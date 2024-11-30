Compile: make

Round trip: 
First start up server with ./Network/round_trip_server 
Then run client for loopback test with ./Network/round_trip_client local 1701 any
Or run client for remote with ./Network/round_trip_client remote 1701 <IPv6 Address>

Bandwidth:
Loopback server : ./Network/bandwidth_server remote
Loopback client : ./Network/bandwidth_client local 1702 any
Remote server : ./Network/bandwidth_server remote
Remote client : ./Network/bandwidth_client remote 1702 <IPv6 Address>

Setup/TearDown:
server : ./Network/setup_teardown_server remote
Loopback client : ./Network/bandwidth_client local 1703 any
Remote client : ./Network/bandwidth_client remote 1703 <IPv6 Address>