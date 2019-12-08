from flask import Flask, jsonify, request, render_template
import subprocess
import json

app = Flask(__name__)

def parse_output(data):
	tmp = data.strip().split('\n')
	num_vertices, num_halfedges, num_faces = tmp[0].split('\t')

	ret = {
		'num_vertices': int(num_vertices),
		'num_halfedges': int(num_halfedges),
		'num_faces': int(num_faces),
		'points': []
	}

	for line in tmp[1:]:
		p1_x, p1_y, p2_x, p2_y, ptype = line.split('\t')

		ret['points'].append({
			'from': (float(p1_x), float(p1_y)),	
			'to': (float(p2_x), float(p2_y)),
			'type': ptype,	
		})

	return ret

@app.route('/api', methods=['POST'])
def api_index():
	params = request.get_json()

	if 'points' in request.form:
		points = request.form['points']
	elif 'points' in params:
		points = params['points']
	else:
		return jsonify({'result': 'fail', 'message': 'param "points" is required'}), 400

	arg = []
	try:
		# points = json.loads(points)
		for p in points:
			arg.append(str(p[0])) # x
			arg.append(str(p[1])) # y

	except Exception as e:
		print(e)
		return jsonify({'result': 'fail', 'message': 'error occurs on parsing param "points"'}), 400


	out = subprocess.check_output(['./cgal_link'] + arg).decode()

	interior, exterior = out.split('\n\n')

	return jsonify({
		'interior': parse_output(interior),	
		'exterior': parse_output(exterior),
	})


@app.route('/')
def index():
	return render_template('main.html')

if __name__ == '__main__':
	app.run(
		host='localhost',
		port=8089,
		debug=True,
	)
