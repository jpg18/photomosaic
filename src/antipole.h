/* antipole.h
 *
 * Copyright (c) 2011, Jeffrey P. Gill
 *
 * This file is part of photomosaic.
 *
 * photomosaic is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * photomosaic is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with photomosaic.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ANTIPOLE_H
#define ANTIPOLE_H 

#define DIST_FUNC double (*dist)( ap_Point *p1, ap_Point *p2 )

typedef struct ap_Point ap_Point;
typedef struct ap_PointList ap_PointList;
typedef struct ap_Cluster ap_Cluster;
typedef struct ap_Tree ap_Tree;

struct ap_Point {
   int id;                    /* point id */
   void *vec;                 /* position vector */
   //double dist_centroid;    /* distance to centroid of cluster */
   ap_PointList *ancestors;   /* list of all ancestors in tree */
};

struct ap_PointList {
   ap_Point *p;               /* point in list */
   double dist;               /* distance to ancestor, centroid, or query */
   ap_PointList *next;        /* pointer to next member of list */
};

struct ap_Cluster {
   ap_Point *centroid;        /* geometric median of cluster */
   //int size;                /* number of points in cluster */
   double radius;             /* distance from centroid to farthest point in cluster */
   ap_PointList *members;     /* list of points in cluster */
};

struct ap_Tree {
   int is_leaf;               /* can be a leaf or an internal node */
   ap_Point *a, *b;           /* if internal node, pointers to antipoles */
   double radius_a, radius_b; /* if internal node, distances from antipoles to their farthest point in cluster */
   ap_Tree *left, *right;     /* if internal node, left and right branches */
   ap_Cluster *cluster;       /* if leaf, pointer to cluster */
};

ap_Tree* build_tree( ap_PointList *set, double target_radius, ap_Point *antipole_a, ap_Point *antipole_b, int dimensionality, DIST_FUNC );
void free_tree( ap_Tree *tree );
ap_Cluster* make_cluster( ap_PointList *set, int dimensionality, DIST_FUNC );
void free_cluster( ap_Cluster *cluster );

void add_point( ap_PointList **set, ap_Point *p, double dist );
void move_point( ap_Point *p, ap_PointList **from, ap_PointList **to );
void move_nth_point( int n, ap_PointList **from, ap_PointList **to );
ap_PointList* copy_list( ap_PointList *set );
void free_list( ap_PointList *set );
int list_size( ap_PointList *set );

void exact_1_median( ap_PointList *set, ap_Point **median, DIST_FUNC );
void approx_1_median( ap_PointList *set, ap_Point **median, int dimensionality, DIST_FUNC );

void exact_antipoles( ap_PointList *set, ap_Point **antipole_a, ap_Point **antipole_b, DIST_FUNC );
void approx_antipoles( ap_PointList *set, ap_Point **antipole_a, ap_Point **antipole_b, int dimensionality, DIST_FUNC );
void adapted_approx_antipoles( ap_PointList *set, ap_Point **antipole_a, ap_Point **antipole_b, double target_radius, DIST_FUNC );
void check_for_antipoles( ap_PointList *set, double target_radius, ap_Point *ancestor, ap_Point **antipole_a, ap_Point **antipole_b );

void range_search( ap_Tree *tree, ap_Point *query, double range, ap_PointList **out, DIST_FUNC );
void range_visit_cluster( ap_Cluster *cluster, ap_Point *query, double range, ap_PointList **out, DIST_FUNC );

void nearest_search( ap_Tree *tree, ap_Point *query, int k, ap_PointList **out, DIST_FUNC );
void nearest_visit_cluster( ap_Cluster *cluster, ap_Point *query, int k, ap_PointList **out, DIST_FUNC );

#endif /* ANTIPOLE_H */

