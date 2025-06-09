from scapy.all import rdpcap, TCP, UDP
import matplotlib.pyplot as plt

def calculate_throughput(pcap_file, interval=1):
    # Read the pcap file
    print(f"Reading pcap file: {pcap_file} ...")
    packets = rdpcap(pcap_file)
    
    # Initialize throughput variables for different flows
    flow1_bytes = 0  # UDP on port 7778
    flow2_bytes = 0  # TCP on port 7777
    flow3_bytes = 0  # TCP on port 7776
    
    # Calculate the duration of the capture
    flow1_start = packets[-1].time
    flow2_start = packets[-1].time
    flow3_start = packets[-1].time

    flow1_end = 0
    flow2_end = 0
    flow3_end = 0

    start_time = packets[0].time
    end_time = packets[-1].time
    duration = end_time - start_time
    print(f"Calculating total bytes for {duration:.2f} seconds...")

    # Process each packet
    for packet in packets:
        packet_size = len(packet)
        
        # Check if the packet is UDP and on port 7778 (flow 1)
        if UDP in packet and packet[UDP].dport == 7778:
            flow1_bytes += packet_size
            flow1_start = min(packet.time, flow1_start)
            flow1_end = max(packet.time, flow1_end)

        # --------Write your code here--------
        # Check if the packet is TCP and on port 7777 (flow 2)
        if TCP in packet and packet[TCP].dport == 7777:
            flow2_bytes += packet_size
            flow2_start = min(packet.time, flow2_start)
            flow2_end = max(packet.time, flow2_end)

        # Check if the packet is TCP and on port 7776 (flow 3)
        if TCP in packet and packet[TCP].dport == 7776:
            flow3_bytes += packet_size
            flow3_start = min(packet.time, flow3_start)
            flow3_end = max(packet.time, flow3_end)

    # Display the total bytes results
    print("Total bytes result:")
    print(f"Flow1 (UDP on port 7778): {flow1_bytes} Bytes")
    print(f"Flow2 (TCP on port 7777): {flow2_bytes} Bytes")
    print(f"Flow3 (TCP on port 7776): {flow3_bytes} Bytes\n")

    # compute bit per second
    flow1_bps = flow1_bytes * 8 / (flow1_end - flow1_start)
    flow2_bps = flow2_bytes * 8 / (flow2_end - flow2_start)
    flow3_bps = flow3_bytes * 8 / (flow3_end - flow3_start)
    
    # Display the bps results
    print("bps result:")
    print(f"Flow1 (UDP on port 7778): {flow1_bps:.2f} bps")
    print(f"Flow2 (TCP on port 7777): {flow2_bps:.2f} bps")
    print(f"Flow3 (TCP on port 7776): {flow3_bps:.2f} bps\n")

    # Return the bps
    return [flow1_bps, flow2_bps, flow3_bps]


# Collect throughput results for each scenario
throughputs_scenario1 = calculate_throughput("udp1M.pcap")
throughputs_scenario2 = calculate_throughput("udp0.5M.pcap")
throughputs_scenario3 = calculate_throughput("udp0.5M_2.pcap")

# Bar graph plotting for each scenario
flows = ['Flow1 (UDP 7778)', 'Flow2 (TCP 7777)', 'Flow3 (TCP 7776)']

# Define colors
colors = ['#A6CEE3', '#B2DF8A', '#FDBF6F']  # Softer blue, green, and orange

# Plot for Scenario 1
plt.figure()
plt.bar(flows, throughputs_scenario1, color=colors, width=0.5)
plt.xlabel('Flows')
plt.ylabel('bps')
plt.title('Long-term Average Throughput for Scenario 1')
plt.savefig('total_data_scenario1.png')
plt.close()  # Close the figure

# Plot for Scenario 2
plt.figure()
plt.bar(flows, throughputs_scenario2, color=colors, width=0.5)
plt.xlabel('Flows')
plt.ylabel('bps')
plt.title('Long-term Average Throughput for Scenario 2')
plt.savefig('total_data_scenario2.png')
plt.close()  # Close the figure

# Plot for Scenario 3
plt.figure()
plt.bar(flows, throughputs_scenario3, color=colors, width=0.5)
plt.xlabel('Flows')
plt.ylabel('bps')
plt.title('Long-term Average Throughput for Scenario 3')
plt.savefig('total_data_scenario3.png')
plt.close()  # Close the figure

print("All graphs have been saved.")