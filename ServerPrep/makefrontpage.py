from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
import MySQLdb
import pandas
deg = u'\N{DEGREE SIGN}'
conn = MySQLdb.connect(host="localhost",user="username",passwd="password",db="data")
cur = conn.cursor()
query = """
SELECT created,temperature,humidity,pressure,heatindex
FROM weather_data
ORDER BY created DESC
LIMIT 1
"""
cur.execute(query)
data = cur.fetchone()
temp = str(data[1])
humi = str(data[2])
pres = str(data[3])
heat = str(data[4])
tempf = str(((data[1]*9)/5)+32)
heatf = str(((data[4]*9)/5)+32)
dewp = str(data[1] - ((100-data[2])/5))
dewpf = str((data[1] - (((100-data[2])/5)*9)/5)+32)
img = Image.open("/var/www/html/wp-content/themes/path-to-header2.jpg")
draw = ImageDraw.Draw(img)
font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 80)
draw.text((100,50),"Temperature:  " + temp + deg +"C/" + tempf + deg + "F",(0,0,0),font=font)
draw.text((100,150),"Humidity:  " + humi + "%",(0,0,0),font=font)
draw.text((100,250),"Pressure:  " + pres + "mBar",(0,0,0),font=font)
draw.text((100,350),"Heat Index:  " + heat + deg +"C/" + heatf + deg + "F",(0,0,0),font=font)
draw.text((100,450),"Dew Point:  " + dewp + deg + "C/" + dewpf + deg + "F",(0,0,0),font=font)
img.save('/var/www/html/wp-content/themes/path-to-header.jpg')
