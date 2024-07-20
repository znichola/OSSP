#include <math.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "raymath.h"

#define N_ASTEROIDS 0

// some basic equations for an orbital system

/*
    Entity to hold the variables needed for an orbital object

    p.x = the projection of the objects position vector in Cartesian space [1 0 0]
    p.y = the projection of the objects position vector in Cartesian space [0 1 0]
    p.z = the projection of the objects position vector in Cartesian space [0 0 1]
    p.x = the projection of the objects velocity vector in Cartesian space [1 0 0]
    p.y = the projection of the objects velocity vector in Cartesian space [0 1 0]
    p.z = the projection of the objects velocity vector in Cartesian space [0 0 1]
    m   = the mass of the object
*/
typedef struct OrbitalEntity
{
    Vector3 p;
    Vector3 v;
    float m;

} OrbitalEntity;

OrbitalEntity *init_inner_solarsystem()
{
    size_t length = sizeof(OrbitalEntity) * (9 + N_ASTEROIDS);

    OrbitalEntity *orbital_entities = malloc(length);

    bzero(orbital_entities, length);

    orbital_entities[0] = (OrbitalEntity){{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.989e30};             // a star similar to the sun
    orbital_entities[1] = (OrbitalEntity){{57.909e9, 0.0, 0.0}, {0.0, 47.36e3, 0.0}, 0.33011e24};  // a planet similar to mercury
    orbital_entities[2] = (OrbitalEntity){{108.209e9, 0.0, 0.0}, {0.0, 35.02e3, 0.0}, 4.8675e24};  // a planet similar to venus
    orbital_entities[3] = (OrbitalEntity){{149.596e9, 0.0, 0.0}, {0.0, 29.78e3, 0.0}, 5.9724e24};  // a planet similar to earth
    orbital_entities[4] = (OrbitalEntity){{227.923e9, 0.0, 0.0}, {0.0, 24.07e3, 0.0}, 0.64171e24}; // a planet similar to mars
    orbital_entities[5] = (OrbitalEntity){{778.570e9, 0.0, 0.0}, {0.0, 13e3, 0.0}, 1898.19e24};    // a planet similar to jupiter
    orbital_entities[6] = (OrbitalEntity){{1433.529e9, 0.0, 0.0}, {0.0, 9.68e3, 0.0}, 568.34e24};  // a planet similar to saturn
    orbital_entities[7] = (OrbitalEntity){{2872.463e9, 0.0, 0.0}, {0.0, 6.80e3, 0.0}, 86.813e24};  // a planet similar to uranus
    orbital_entities[8] = (OrbitalEntity){{4495.060e9, 0.0, 0.0}, {0.0, 5.43e3, 0.0}, 102.413e24}; // a planet similar to neptune

    return orbital_entities;
}

void pvec(Vector3 v, char *msg)
{
    printf("%s(%e, %e, %e)\n", msg, v.x, v.y, v.z);
}

void porb(OrbitalEntity o)
{
    printf("pos: ");
    pvec(o.p, "");
    printf("vel: ");
    pvec(o.v, "");
    printf("mass: %e\n", o.m);
}

void pv(float t_0, float t, float dt)
{
    printf("t_0=%e t=%e dt=%e\n", t_0, t, dt);
}

void propagation(OrbitalEntity *orbital_entities)
{
    float t_0 = 0.0f;
    float t = t_0;
    float dt = 60.0f * 60.0f * 24.0f;  // one day in seconds
    float t_end = dt * 365.0f * 10.0f; // approximately a decade in seconds
    float BIG_G = 6.67E-11f;           // gravitational constant

    printf("start: t_0=%e t=%e dt=%e\n", t_0, t, dt);

    int tmp = 0;

    while (t < t_end)
    {
        printf("\n###################\n");
        for (size_t m1_idx = 0; m1_idx < 9 + N_ASTEROIDS; m1_idx++)
        {
            Vector3 a_g = Vector3Zero();
            for (size_t m2_idx = 0; m2_idx < 9 + N_ASTEROIDS; m2_idx++)
            {
                if (m2_idx != m1_idx)
                {
                    Vector3 r_vector;

                    porb(orbital_entities[m1_idx]);

                    r_vector = Vector3Subtract(orbital_entities[m1_idx].p, orbital_entities[m2_idx].p);
                    float r_mag = Vector3Length(r_vector);

                    float acceleration = -1.0f * BIG_G * (orbital_entities[m2_idx].m) / powf(r_mag, 2.0f);

                    printf("\n\n -1.0f * BIG_G = %e\n", -1.0f * BIG_G);
                    printf("\n\n BIG_G = %.20e\n", BIG_G);
                    printf("\n\n BIG_G multi qirh pow = %e\n", -1.0f * BIG_G * powf(10, 11));

                    printf("\n");
                    printf("r_mag: %e acceleration: %e\n", r_mag, acceleration);
                    printf("\n");
                    printf("powf(r_mag, 2.0) = %e\n", powf(r_mag, 2.0f));

                    printf("-1.0f * BIG_G * (orbital_entities[m2_idx].m) = %e\n", -1.0f * BIG_G * (orbital_entities[m2_idx].m));

                    printf("-1.0f * BIG_G * (orbital_entities[m2_idx].m) / powf(r_mag, 2.0f) = %e\n", -1.0f * BIG_G * (orbital_entities[m2_idx].m) / powf(r_mag, 2.0f));

                    printf("\n");

                    Vector3 r_unit_vector = Vector3Normalize(r_vector);

                    a_g = Vector3Add(a_g, Vector3Scale(r_unit_vector, acceleration));
                    pvec(a_g, "a_g");
                    pvec(r_vector, "r_vector");
                    exit(0);
                }
            }

            orbital_entities[m1_idx].v = Vector3Add(orbital_entities[m1_idx].v, Vector3Scale(a_g, dt));
        }

        for (size_t entity_idx = 0; entity_idx < 9 + N_ASTEROIDS; entity_idx++)
        {
            orbital_entities[entity_idx].p = Vector3Add(orbital_entities[entity_idx].p, Vector3Scale(orbital_entities[entity_idx].v, dt));
        }

        t += dt;

        if (tmp > 0)
            return;
        tmp++;
        printf("%e, %e, %e\n", orbital_entities[4].p.x, orbital_entities[4].p.y, orbital_entities[4].p.z);
    }
}

void run_sim()
{
    OrbitalEntity *ents = init_inner_solarsystem();

    propagation(ents);

    printf("we done it");
}