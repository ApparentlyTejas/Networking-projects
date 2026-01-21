#!/usr/bin/env python3
import requests
import pprint
import sys

ONOS_URL = "http://localhost:8181/onos/v1"
USERNAME = "onos"
PASSWORD = "rocks"

GROUP = 3
MGM_IPS = ["192.168.100.30", "192.168.100.31", "192.168.100.32"]

headers = {"Accept": "application/json"}

def main():
    print(f"ONOS REST API - Group 33 Switches (adn37@faui7t1)")
    print("=" * 70)

    print("1. Querying all devices...")
    resp = requests.get(f"{ONOS_URL}/devices", 
                       auth=(USERNAME, PASSWORD), 
                       headers=headers)
    
    if resp.status_code != 200:
        print(f"ERROR: {resp.status_code} - Check SSH tunnel!")
        sys.exit(1)
    
    devices = resp.json()["devices"]
    group_switches = {}
    
    for device in devices:
        # FIXED: annotations.managementAddress
        mgmt_ip = device.get("annotations", {}).get("managementAddress", "")
        if mgmt_ip in MGM_IPS:
            print(f"Found {mgmt_ip} → ID: {device['id']}")
            group_switches[mgmt_ip] = device["id"]
    
    if not group_switches:
        print("No group switches found! Check group number.")
        sys.exit(1)
    
    print("\n2. Getting port details...")
    for ip, device_id in group_switches.items():
        print(f"\n {ip} ({device_id})")
        port_resp = requests.get(f"{ONOS_URL}/devices/{device_id}/ports",
                                auth=(USERNAME, PASSWORD),
                                headers=headers)
        
        if port_resp.status_code == 200:
            ports = port_resp.json()["ports"]
            print(f"   Ports: {len(ports)}")
            pprint.pprint(ports, width=60, indent=4)
        else:
            print(f"   Port query failed: {port_resp.status_code}")
    
    print("\n DONE")

if __name__ == "__main__":
    main()
