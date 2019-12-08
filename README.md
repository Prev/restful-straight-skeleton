# RESTful Straight Skeleton

RESTful API server for [Straight Skeleton](https://en.wikipedia.org/wiki/Straight_skeleton) using [CGAL](https://doc.cgal.org/latest/Straight_skeleton_2/index.html).  
API server is implemented with Flask, using `subprocess` module to call CGAL.


### How to run server

Installation of CGAL and its dependencys will be done while building a docker image.  
Default port of API server is `80`. Use `-p` option to expose at specific port.


```
$ docker build -t cgal_api .
$ docker run --name cgal_api -p 8080:80 cgal_api
```


### How to use API

Sample code for calling the API is located in the container.  
Open `http://localhost:8080` to see simple demo, or write a code like below:


```javascript
var body = {
	'points': [[-1,-1], [0,-12], [1,-1], [12,0], [1,1], [0,12], [-1,1], [-12,0]]
};
var res = await fetch('http://localhost:8080/api', {
	method: 'POST',
	headers: {
		'Content-Type': 'application/json',
	},
	body: JSON.stringify(body),
});
var data = await res.json();
console.log(data);
```
