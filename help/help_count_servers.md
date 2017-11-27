count servers
=============

Syntax:

	count servers [received_points/selected_points] [where ...]

Count servers returns the number of servers in a SiriDB cluster.
Received points are the number of points received by a server since uptime.
After a restart the received points counters are reset to zero.


>**Info**
>
>Received points only shows the number of points after uptime. For the total
>number of points you can use `count series length`

Examples:

	# Get number of servers
	count servers

	# Get number of servers in pool 0
	count servers where pool == 0

	# Get total number of received points since uptime
	count servers received_points

	# Get total number of selected (queried) points since uptime
	count servers selected_points

Example output (count servers):

	{"servers": 6}

Example output (count servers received_points):

    {"servers_received_points": 21573435683}
