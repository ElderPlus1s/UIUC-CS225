#include "scene.h"
#include "image.h"

#include <iostream>

using namespace std;

Scene::Scene(int max){
	maxLayers = max;
	layers = new Image * [max];

	xCoord = new int[max];
	yCoord = new int[max];

	for (int i = 0; i < max; i++){
		layers[i] = NULL;
	}
}



Scene::~Scene(){
	clear();
}

Scene::Scene(const Scene & source){
	layers = new Image*[maxLayers];
	maxLayers = source.maxLayers;
	xCoord = new int[maxLayers];
	yCoord = new int[maxLayers];

	for(int i = 0; i < maxLayers ; i++){
		xCoord[i] = source.xCoord[i];
		yCoord[i] = source.yCoord[i];

		if(source.layers[i]==NULL){
			layers[i] = NULL;
		}

		else{
			layers[i] = new Image(*source.layers[i]);
		}
	}
}

const Scene & Scene::operator= (const Scene &source){
	clear();
	copy(source);

	return *this;
}


void Scene::clear(){
	for (int i = 0; i < maxLayers){
		delete layers[i];
		layers[i] = NULL;
	}

	delete [] layers;
	layers = NULL;
	delete [] xCoord;
	xCoord = NULL;
	delete [] yCoord;
	yCoord = NULL;
}

void Scene::copy(const Scene & source){
	maxLayers = source.maxLayers;
	layers = new Image*[maxLayers];
	xCoord = new int[maxLayers];
	yCoord = new int[maxLayers];

	for(int i = 0; i < maxLayers ; i++){
		xCoord[i] = source.xCoord[i];
		yCoord[i] = source.yCoord[i];

		if(source.layers[i]==NULL){
			layers[i] = NULL;
		}

		else{
			layers[i] = new Image(source.layers[i]);
		}
	}
}