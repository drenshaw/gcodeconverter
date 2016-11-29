import math
import matplotlib.pyplot as plt

def show_points(points):
	'''
	Plot the points on the map.
	'''
	for point in points:
		plt.scatter(point[0], point[1])

	for i in range(len(points)):
		#plt.plot(points[i], points[(i+1) % len(points)], 'k-', lw=2)
		plt.plot([points[i][0], points[(i+1) % len(points)][0]], [points[i][1], points[(i+1) % len(points)][1]], 'k-')
		plt.pause(0.01)
	#plt.show()

def in_collision(point):
	'''
	Determines if a point is in collision with the single obstacle we have. 
	Assume, a global obstacle for simulation purpose
	'''
	#Find out two nearby points, based on theta of current point. 
	pass

def extend(point, center, epsilon):
	'''
	Extend point towards center by epsilon
	'''
	#return center if point and center are within epsilon from each other
	if get_magnitude(get_vector(point, center)) < epsilon:
		#print "converged ", center
		return list(center)
	#find magnitude of vector v, from point towards the center. Convert it to unit vector. Add unit vector to the point
	v_mag = 0
	for i in range(len(point)):
		v_mag += (point[i] - center[i]) ** 2
	v_mag = v_mag ** 0.5
	#q_near is point, q is center
	extendPoint = [float(point[i] + ((center[i] - point[i]) / v_mag) * epsilon) for i in range(len(point))]
	return extendPoint

def scale_vector(vector, scale):
	return [float(vector[i] * scale) for i in range(len(vector))]

def translate_vector(point, vector):
	'''
	translate a vector to a 2d point
	'''
	return [float(point[i] + vector[i]) for i in range(len(vector))]
	
def get_vector(ptA, ptB):
	'''
	get a vector from ptA to ptB
	'''
	return [float(ptB[i] - ptA[i]) for i in range(len(ptA))]

def get_magnitude(vector):
	'''
	returns magnitude of a vector.
	'''
	v_mag = 0
	for i in range(len(vector)):
		v_mag += (vector[i]) ** 2
	return v_mag ** 0.5
	
def get_radius(points):
	'''
	returns maximum possible radius from centroid.
	'''
	radius = 0
	center = get_center(points)
	#print 'center is ', center
	for point in points:
		dist = ((center[0] - point[0]) ** 2 +  (center[1] - point[1]) ** 2) ** 0.5
		if radius < dist:
			radius = dist
	return radius


def get_center(points):
	'''
	returns centroid of set of 2d points. 
	'''
	sigma_x = 0.0
	sigma_y = 0.0
	for point in points:
		sigma_x += point[0]
		sigma_y += point[1]
	center = (sigma_x / len(points), sigma_y / len(points))
	return center
		
def magnified_cover(points, epsilon):
	'''
	get a magnified boundry that is *at least* epsilon away from the actual point
	'''
	center = get_center(points)
	radius = get_radius(points)
	#print 'radius is ', radius
	boundry = []
	for point in points:
		#get unit vector in the direction from center to point. Scale it to (radius + epsilon). Position one endpoint of vector on the center
		vecP = get_vector(center, point)
		magVecP = get_magnitude(vecP)
		unitP = scale_vector(vecP, 1.0 / magVecP)
		scaled_vec = scale_vector(unitP, radius + epsilon)
		#translate the vector to the origin
		boundry.append(translate_vector(center, scaled_vec))
	return boundry
	
def get_points(fileName, z = None, counter = 1, epsilon = 1):
	'''
	Parse the file and return a list of points that satisfy z. If z is None, the file contains 2d points
	counter: Pick every counter'th point for a Z
	'''
	currentCounter = 0
	f = open(fileName)
	#parse the co-ordinates
	#print counter
	points = []
	for line in f:
		array = line.split()
		if z != None:
			if abs(float(array[2]) - z) < epsilon:
				#print "found point"
				point = (float(array[0]), float(array[1]))
				currentCounter += 1
				if currentCounter % counter == 0:
					points.append(point)
		else:
			point = (float(array[0]), float(array[1]))
			points.append(point)
	return points

def orderPoints(points):
	'''
	order points in an order that scanner can use to scan
	'''
	center = get_center(points)
	points_orientation = []
	for i in range(len(points)):
		dy = (points[i][1] - center[1])
		dx = (points[i][0] - center[0])
		points_orientation.append((points[i][0], points[i][1], math.degrees(math.atan2(dy, dx))))
	#perform the ordering on the points
	points_orientation.sort(key=lambda tup: tup[2])
	#print points_orientation
	#remove theta from the list before returning
	answer = [points_orientation[i][:len(points_orientation[i])-1] for i in range(len(points_orientation))]
	#print "answer", answer
	return answer

def rubber_band_iteration(wrap, obstacle, epsilon):
	'''
	contract wrap towards obstacle each point by epsilon. It point is in collision, do nothing
	'''
	bConverged = True
	for i in range(len(wrap)):
		prevPoint = wrap[i][:]
		wrap[i] = extend(wrap[i], obstacle[i], epsilon)
		if wrap[i] != prevPoint:
			bConverged = False
	return (wrap, bConverged)

#points = get_points('data.txt')
points = get_points('3d_data.txt', 6, 1, 1)
#print len(points)
#print points
points = orderPoints(points)
#print "ordered ", points
magnified = magnified_cover(points, 1)
#print magnified
bConverged = False
while not bConverged:
	magnified = rubber_band_iteration(magnified, points, 0.2)
	bConverged = magnified[1]
	print "intermediate boundry"
	magnified = magnified[0]
	#print magnified
	for point in magnified:
		print '%04f %04f 6' % (point[0], point[1])
	#print len(magnified)
	#show_points(magnified) #To display points
#plt.show() #To display points
print "Final converged boundry"
for point in magnified:
	print '%04f %04f 6' % (point[0], point[1])
