import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import pandas
import MySQLdb
conn = MySQLdb.connect(host="localhost", user="username", passwd="password", db="data")
query = """
SELECT created, temperature, humidity, heatindex
FROM weather_data
WHERE created >= CURDATE() - INTERVAL 1 DAY
"""
df = pandas.read_sql(query, conn, index_col=['created'])
fig, ax = plt.subplots()
df.plot(ax=ax)
fig.savefig('/var/www/html/wp-content/uploads/path-to-daily.jpg', dpi=100)
conn.close()
conn = MySQLdb.connect(host="localhost", user="username", passwd="password", db="data")
query = """
SELECT created, pressure
FROM weather_data
WHERE created >= CURDATE() - INTERVAL 1 DAY
"""
df = pandas.read_sql(query, conn, index_col=['created'])
fig, ax = plt.subplots()
df.plot(ax=ax)
fig.savefig('/var/www/html/wp-content/uploads/path-to-dailyp.jpg', dpi=100)
conn.close()
