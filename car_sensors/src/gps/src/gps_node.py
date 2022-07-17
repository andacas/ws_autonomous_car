#!/usr/bin/env python3
import serial
import pynmea2
import rospy
import math
import re
# Convert NMEA absolute position to decimal degrees "ddmm.mmmm" or "dddmm.mmmm" really is D+M/60, then negated if quadrant is 'W' or 'S'
from std_msgs.msg import String
from sensor_msgs.msg import NavSatFix
class publishGPS(object):
    def __init__(self):
        rospy.loginfo("Initialising GPS publishing")
        self.gps_pub=rospy.Publisher('/gps', NavSatFix, queue_size=1)
        rospy.sleep(4)
        rospy.loginfo("initialised")
    def do_work(self):
        str = serialPort.readline().decode()
        if str.find('GGA') > 0:
            msg = pynmea2.parse(str)
            print ("Timestamp: %s -- Lat: %s %s -- Lon: %s %s -- Altitude: %s %s" % (msg.timestamp,msg.lat,msg.lat_dir,msg.lon,msg.lon_dir,msg.altitude,msg.altitude_units))
            gpsmsg=NavSatFix()
            gpsmsg.header.stamp = rospy.Time.now()
            gpsmsg.header.frame_id = "gps"
            gpsmsg.latitude=float(msg.latitude)
            gpsmsg.longitude=float(msg.longitude)
            gpsmsg.altitude = float(msg.altitude)
            self.gps_pub.publish(gpsmsg)
            rospy.sleep(1)
    def run(self):
        r=rospy.Rate(1)
        while not rospy.is_shutdown():
            self.do_work()

if __name__=='__main__':
    port = rospy.get_param("gps_port_name")
    serialPort = serial.Serial(port, 9600, timeout=0.5)
    rospy.init_node('pubgps')
    obj=publishGPS()
    obj.run()
