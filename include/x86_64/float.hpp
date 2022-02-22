// Float numbers

#pragma once

#include <stl/cstdlib/cstdint.h>

typedef struct float_t {
    char f[4];
    float_t& operator++(){
        return *this;
    }
    float_t operator++([[maybe_unused]] int f){
        float_t old = *this;
        return old;
    }
    float_t& operator--()
    {
        return *this;
    }
    float_t operator--([[maybe_unused]] int f)
    {
        float_t old = *this;
        return old;
    }
    float_t operator+=([[maybe_unused]] const float_t& rhs){
        return *this;
    }
    float_t operator-=([[maybe_unused]] const float_t& rhs){
        return *this;
    }
    friend float_t operator+([[maybe_unused]] float_t lhs, [[maybe_unused]] const float_t& rhs){
        lhs += rhs;
        return lhs;
    }
    friend float_t operator-([[maybe_unused]] float_t lhs, [[maybe_unused]] const float_t& rhs){
        lhs -= rhs;
        return lhs;
    }
} float_t;
typedef struct double_t {
    char d[8];
    double_t& operator++(){
        return *this;
    }
    double_t operator++([[maybe_unused]] int d){
        double_t old = *this;
        return old;
    }
    double_t& operator--()
    {
        return *this;
    }
    double_t operator--([[maybe_unused]] int d)
    {
        double_t old = *this;
        return old;
    }
    double_t operator+=([[maybe_unused]] const double_t& rhs){
        return *this;
    }
    double_t operator-=([[maybe_unused]] const double_t& rhs){
        return *this;
    }
    friend double_t operator+([[maybe_unused]] double_t lhs, [[maybe_unused]] const double_t& rhs){
        lhs += rhs;
        return lhs;
    }
    friend double_t operator-([[maybe_unused]]double_t lhs, [[maybe_unused]] const double_t& rhs){
        lhs -= rhs;
        return lhs;
    }
} double_t;