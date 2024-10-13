#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL2_gfxPrimitives.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

template <typename T>
class Manager
{
public:
	static T* instance(){
		if (!instance_mg)
			instance_mg = new T;
		return instance_mg;
	}

private:
	static T* instance_mg;

protected:
	Manager()=default;
	~Manager()=default;

	Manager(const T&) = delete;
	T& operator=(const T&) = delete;
};
template <typename T>
T* Manager<T>::instance_mg = nullptr;

