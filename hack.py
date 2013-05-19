import socket
import httplib, urllib
import json
import requests

a = [0, 1, 8, 16, 46, 74, 96, 106, 109, 126, 127, 186, 192, 255]
count = 0
f = open('outfile', 'a')
payload = {'name': 'Vanshil'}


#try:
#	r = requests.post("http://%d.%d.%d.%d/hackerolympics.json" % (96, 126, 109, 46), data = payload, timeout = 0.05)
#	print "Connection established with %d.%d.%d.%d" % (96, 126, 109, 46)
#	try:
#		strbuf = str(r.json())
#		f.write(strbuf)	
#	except ValueError:
#		print "Useless connection"
#except (requests.exceptions.ConnectionError,  requests.exceptions.Timeout, socket.timeout):
#	print "Connection with %d.%d.%d.%d failed" % (74, 16, 106, 109)

for b in a:
	for c in a:
		for d in a:
			for e in a:
				if b!=c and b!=d and b!=e and c!=d and c!=e and d!=e:
					try:
						r = requests.post("http://%d.%d.%d.%d/hackerolympics.json" % (b, c, d, e), data = payload, timeout = 0.05)
						print "Connection established with %d.%d.%d.%d" % (b, c, d, e)
						f.write("Connection established with %d.%d.%d.%d\n" % (b, c, d, e))
						try: 
							strbuf = str(r.json())
							f.write(strbuf)
							f.write("\n")
						except ValueError:
							print "Useless connection" 	
							
					except (requests.exceptions.ConnectionError,  requests.exceptions.Timeout, socket.timeout):
						print "Connection with %d.%d.%d.%d failed" % (b, c, d, e)
									
