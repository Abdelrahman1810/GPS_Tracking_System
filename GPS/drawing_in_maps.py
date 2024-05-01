#######################
# Abdelrahman 2100347 #
#######################
import re
import folium

# Open cordinates file
with open('cordenates.txt', 'r') as f:
    content = f.read()

# extract all numbers in lines from the file 
pattern = r'[-+]?\d*\.\d+'

# Find all float numbers in the file
float_numbers = re.findall(pattern, content)

# create an array for points
points = []
for x in range(len(float_numbers)):
   points.append("{:.6f}".format(float(float_numbers[x])))

num_cordenates = len(points)
num_point = len(points)//2

# Identify start and end point 
start_lat, start_lon = points[0], points[1]
end_lat, end_lon = points[num_cordenates - 2], points[num_cordenates - 1]

# creat a map start point and auto zoom in it
map = folium.Map(location=[start_lat, start_lon], zoom_start=18)
# add marks for end and start point
markers = [
    folium.Marker([start_lat, start_lon], popup='START', icon=folium.Icon(color='darkblue', icon='start')),
    folium.Marker([end_lat, end_lon], popup='END', icon=folium.Icon(color='red', icon='end')),
]

# add markers to the map
for marker in markers:
    marker.add_to(map)

# add cordinates of transaction so Line will not be straight line
trail_coordinates = []
for x in range(0,num_cordenates,2):
    trail_coordinates.append((float(points[x]),float(points[x+1])))

# extract the map
kw = {"opacity": 0.89, "weight": 5}
folium.PolyLine(
    trail_coordinates,
    smooth_factor=3,
    line_cap="butt",
    tooltip="GPS_road",
    color="green",
    opacity = 0.89,
    weight = 3,
    ).add_to(map)

map.save('map.html')