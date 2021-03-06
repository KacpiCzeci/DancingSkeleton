#pragma once
#ifndef SCENE_CONST_H
#define SCENE_CONST_H
#include <vector>;

std::vector<float> verts = {
		10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -2.0f, 10.0f, 1.0f,

		10.0f, -2.0f, 10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -5.0f, 10.0f, 1.0f,

		//
		10.0f, -2.0f, 10.0f, 1.0f,
		10.0f, -5.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, 10.0f, 1.0f,

		-10.0f, -2.0f, 10.0f, 1.0f,
		10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, 10.0f, 1.0f,

		//
		-10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,

		-10.0f, -2.0f, -10.0f, 1.0f,
		-10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,

		//
		-10.0f, -2.0f, -10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,

		-10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -2.0f, -10.0f, 1.0f,

		//
		10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -2.0f, -10.0f, 1.0f,

		-10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -2.0f, 10.0f, 1.0f,

		//
		10.0f, -5.0f, 10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,

		-10.0f, -5.0f, 10.0f, 1.0f,
		10.0f, -5.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f
};

std::vector<float> tc = {
		0.0f, 0.15f,
		0.0f, 0.0f,
		1.0f, 0.15f,

		1.0f, 0.15f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		//
		1.0f, 0.15f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.15f,
		1.0f, 0.15f,
		0.0f, 0.0f,

		//
		1.0f, 0.15f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.15f,
		1.0f, 0.15f,
		0.0f, 0.0f,

		//
		0.0f, 0.15f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 0.15f,
		1.0f, 0.0f,
		1.0f, 0.15f,

		//
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,

		//
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f
};
#endif