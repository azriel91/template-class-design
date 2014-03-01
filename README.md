template-class-design
=====================

Test design for a c++ module with templated classes. This project gives an example of using the interface-segregation principle to structure classes. In this project, consumers of an ``ImageStore`` are able to receive any implementation of it, without requiring knowledge of the actual type of image class that is used, while maintaining type safety of the ``Image`` class through templates.

## Pre-requisites

* g++ 4.8
* [maven 3](http://maven.apache.org/download.cgi)

## Compiling

1. Install the google mock library.
	1. Download [googlemock](https://code.google.com/p/googlemock/downloads/list) 1.7.0
	2. Extract the google mock library, and drop this [pom.xml](https://github.com/azriel91/cpp-maven-support/blob/master/gmock/pom.xml) into the directory.
	3. In the googlemock directory, run ``mvn install``
2. In the repository checkout directory, run ``mvn test``
