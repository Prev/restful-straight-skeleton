FROM tiangolo/uwsgi-nginx-flask:python3.6

RUN apt-get update && \
	apt-get install -y libcgal-dev libboost-all-dev libboost-thread-dev cmake

COPY ./cgal_front /tmp/cgal_front

RUN cd /tmp/cgal_front && \
	mkdir build && \
	cd build && \
	cmake -DCGAL_DIR=/usr/include/CGAL/ -DCMAKE_BUILD_TYPE=Release .. && \
	make && \
	mv cgal_link /app

# COPY requirements.txt /tmp/
# RUN pip install -r /tmp/requirements.txt && \
# 	rm /tmp/requirements.txt

COPY ./api_server /app
