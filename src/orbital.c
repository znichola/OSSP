#include <math.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "raymath.h"

#define N_ASTEROIDS 0

// some basic equations for an orbital system

/*
    Entity to hold the variables needed for an orbital object

    e[0] = x,  the projection of the objects position vector in Cartesian space [1 0 0]
    e[1] = y,  the projection of the objects position vector in Cartesian space [0 1 0]
    e[2] = z,  the projection of the objects position vector in Cartesian space [0 0 1]
    e[3] = xp, the projection of the objects velocity vector in Cartesian space [1 0 0]
    e[4] = yp, the projection of the objects velocity vector in Cartesian space [0 1 0]
    e[5] = zp, the projection of the objects velocity vector in Cartesian space [0 0 1]
    e[6] = m, the mass of the object
*/

typedef struct OrbitalEntity
{
    double e[7];
} OrbitalEntity;

OrbitalEntity *init_inner_solarsystem()
{
    size_t length = sizeof(OrbitalEntity) * (9 + N_ASTEROIDS);

    OrbitalEntity *orbital_entities = malloc(length);

    bzero(orbital_entities, length);

    orbital_entities[0] = (OrbitalEntity){.e = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.989e30}};             // a star similar to the sun
    orbital_entities[1] = (OrbitalEntity){.e = {57.909e9, 0.0, 0.0, 0.0, 47.36e3, 0.0, 0.33011e24}};  // a planet similar to mercury
    orbital_entities[2] = (OrbitalEntity){.e = {108.209e9, 0.0, 0.0, 0.0, 35.02e3, 0.0, 4.8675e24}};  // a planet similar to venus
    orbital_entities[3] = (OrbitalEntity){.e = {149.596e9, 0.0, 0.0, 0.0, 29.78e3, 0.0, 5.9724e24}};  // a planet similar to earth
    orbital_entities[4] = (OrbitalEntity){.e = {227.923e9, 0.0, 0.0, 0.0, 24.07e3, 0.0, 0.64171e24}}; // a planet similar to mars
    orbital_entities[5] = (OrbitalEntity){.e = {778.570e9, 0.0, 0.0, 0.0, 13e3, 0.0, 1898.19e24}};    // a planet similar to jupiter
    orbital_entities[6] = (OrbitalEntity){.e = {1433.529e9, 0.0, 0.0, 0.0, 9.68e3, 0.0, 568.34e24}};  // a planet similar to saturn
    orbital_entities[7] = (OrbitalEntity){.e = {2872.463e9, 0.0, 0.0, 0.0, 6.80e3, 0.0, 86.813e24}};  // a planet similar to uranus
    orbital_entities[8] = (OrbitalEntity){.e = {4495.060e9, 0.0, 0.0, 0.0, 5.43e3, 0.0, 102.413e24}}; // a planet similar to neptune

    return orbital_entities;
}

void propagation(OrbitalEntity *orbital_entities)
{
    double t_0 = 0;
    double t = t_0;
    double dt = 60 * 60 * 24;     // one day in seconds
    double t_end = dt * 365 * 10; // approximately a decade in seconds
    double BIG_G = 6.67e-11;      // gravitational constant
    
    int tmp = 0;

    while (t < t_end)
    {
        for (size_t m1_idx = 0; m1_idx < 9 + N_ASTEROIDS; m1_idx++)
        {
            Vector3 a_g = {0, 0, 0};

            for (size_t m2_idx = 0; m2_idx < 9 + N_ASTEROIDS; m2_idx++)
            {
                if (m2_idx != m1_idx)
                {
                    Vector3 r_vector;

                    r_vector.x = orbital_entities[m1_idx].e[0] - orbital_entities[m2_idx].e[0];
                    r_vector.y = orbital_entities[m1_idx].e[1] - orbital_entities[m2_idx].e[1];
                    r_vector.z = orbital_entities[m1_idx].e[2] - orbital_entities[m2_idx].e[2];

                    double r_mag = sqrt(
                        r_vector.x * r_vector.x + r_vector.y * r_vector.y + r_vector.z * r_vector.z);

                    double acceleration = -1.0 * BIG_G * (orbital_entities[m2_idx].e[6]) / pow(r_mag, 2.0);

                    Vector3 r_unit_vector = {r_vector.x / r_mag, r_vector.y / r_mag, r_vector.z / r_mag};

                    a_g.x += acceleration * r_unit_vector.x;
                    a_g.y += acceleration * r_unit_vector.y;
                    a_g.z += acceleration * r_unit_vector.z;
                }
            }

            orbital_entities[m1_idx].e[3] += a_g.x * dt;
            orbital_entities[m1_idx].e[4] += a_g.y * dt;
            orbital_entities[m1_idx].e[5] += a_g.z * dt;
        }

        for (size_t entity_idx = 0; entity_idx < 9 + N_ASTEROIDS; entity_idx++)
        {
            orbital_entities[entity_idx].e[0] += orbital_entities[entity_idx].e[3] * dt;
            orbital_entities[entity_idx].e[1] += orbital_entities[entity_idx].e[4] * dt;
            orbital_entities[entity_idx].e[2] += orbital_entities[entity_idx].e[5] * dt;
        }

        t += dt;
        
        if (tmp > 10) return;
        printf("%f, %f, %f\n", orbital_entities[4].e[0], orbital_entities[3].e[1], orbital_entities[3].e[2]);
    }
}

void run_sim() {
    OrbitalEntity * ents = init_inner_solarsystem();

    propagation(ents);

    printf("we done it");
}