/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "shooters.h"

struct seg
{
    float m,q;
    point A,B;
};

bool CheckCollision(point A, point B, point C, int radius)
{
    float dist;

    if(A.x==B.x)
    {
        if(A.y>B.y)
        {
            if(C.y>A.y) dist = distance(A,C);
            else if(C.y<B.y) dist = distance(B,C);
            else dist = abs(A.x-C.x);
        }
        else
        {
            if(C.y<A.y) dist = distance(A,C);
            else if(C.y>B.y) dist = distance(B,C);
            else dist = abs(A.x-C.x);
        }
    }

    else if(A.y==B.y)
    {
        if(A.x>B.x)
        {
            if(C.x>A.x) dist = distance(A,C);
            else if(C.x<B.x) dist = distance(B,C);
            else dist = abs(A.y-C.y);
        }
        else
        {
            if(C.x<A.x) dist = distance(A,C);
            else if(C.x>B.x) dist = distance(B,C);
            else dist = abs(A.y-C.y);
        }
    }

    else
    {
        //segmento che delimita il muro
        seg segment;
        segment.A = A;
        segment.B = B;
        segment.m = (A.y-B.y) / (A.x-B.x);
        segment.q = A.y - segment.m*A.x;

        //segmento perpendicolare alla prima e passanto per C, incognita è segment1.B
        seg segment1;
        segment1.A = C;
        segment1.m = -(1/segment.m);
        segment1.q = C.y - segment1.m*C.x;
        segment1.B.x = (segment1.q-segment.q) / (segment.m-segment1.m);
        segment1.B.y = segment.m*segment1.B.x + segment.q;

        //check if segment1.B is in the segment
        if(inside(segment1.B,A,B)) dist = distance(segment1.A, segment1.B);
        else
        {/* doesn't work

            float dist1;
            dist = distance(segment1.B, A);
            dist1 = distance(segment1.B, B);
            if(dist1 < dist) dist = dist1;*/
            return false;
        }
    }

    if(dist <= radius) return true;
    else return false;
}

float distance(point A, point B)
{
    float ret = pow(A.x-B.x, 2) + pow(A.y-B.y, 2);
    return sqrt(ret);
}

bool inside(point P, point A, point B)
{
    bool inX=false, inY=false;
    if(A.x>B.x)
    {
        if(P.x<A.x && P.x>B.x)
            inX = true;
    }
    else
    {
        if(P.x>A.x && P.x<B.x)
            inX = true;
    }

    if(A.y>B.y)
    {
        if(P.y<A.y && P.y>B.y)
            inY = true;
    }
    else
    {
        if(P.y>A.y && P.y<B.y)
            inY = true;
    }

    if(inX && inY) return true;
    else return false;
}
