//
//  TriLUT.h
//  Arcs
//
//  Created by tom on 4/25/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"

#define DEG_TO_RAD 0.017453292519943295769236907684886f

class TriLUT{
private:
    float * sinLUT;
    float * cosLUT;
    
    float SINCOS_PRECISION = 1.0;
    int   SINCOS_LENGHT =  int((360.0 / SINCOS_PRECISION ));
    
public:
    TriLUT(){
        sinLUT = new float[SINCOS_LENGHT];
        cosLUT = new float[SINCOS_LENGHT];
        
        ci::app::console()<<"COS SIN LENGHT LUT"<<std::endl;
        ci::app::console()<<SINCOS_LENGHT<<std::endl;
        
        for(int i = 0; i < SINCOS_LENGHT; i++){
            sinLUT[i] = (float) ci::math<float>::sin( i * DEG_TO_RAD * SINCOS_PRECISION );
            cosLUT[i] = (float) ci::math<float>::cos( i * DEG_TO_RAD * SINCOS_PRECISION );
        }
    }
    
    int   getLenght(){ return SINCOS_LENGHT;}
    float getPrecision(){ return SINCOS_PRECISION;}
    
    inline float getSIN(int i);
    inline float getCOS(int i);
    
};

float TriLUT::getSIN(int i)
{
    return sinLUT[i];
}

float TriLUT::getCOS(int i)
{
    return cosLUT[i];
}