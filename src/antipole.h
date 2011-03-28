#ifndef ANTIPOLE_H
#define ANTIPOLE_H 

struct ap_Point {
   int id;                       /* point id */
   void *vec;                    /* position vector */
   //double dist_centroid;       /* distance to centroid of cluster */
   struct ap_List *ancestors;    /* list of all ancestors in tree */
};

struct ap_List {
   struct ap_Point *p;           /* point in list */
   double dist;                  /* distance to ancestor or centroid */
   struct ap_List *next;         /* pointer to next member of list */
};

struct ap_Cluster {
   struct ap_Point *centroid;    /* geometric median of cluster */
   //int size;                   /* number of points in cluster */
   double radius;                /* distance from centroid to farthest point in cluster */
   struct ap_List *neighbors;    /* list of points in cluster */
};

struct ap_Tree {
   int is_leaf;                  /* can be a leaf or an internal node */
   struct ap_Point *a, *b;       /* if internal node, pointers to antipoles */
   double radius_a, radius_b;    /* if internal node, distances from antipoles to their farthest point in cluster */
   struct ap_Tree *left, *right; /* if internal node, left and right branches */
   struct ap_Cluster *cluster;   /* if leaf, pointer to cluster */
};

struct ap_Tree* build_tree( struct ap_List *set, double radius, struct ap_List *antipoles, double (*dist)( struct ap_Point *p1, struct ap_Point *p2 ) );
struct ap_Cluster* make_cluster( struct ap_List *set, double (*dist)( struct ap_Point *p1, struct ap_Point *p2 ) );
void add_point( struct ap_List **set, struct ap_Point *p, double dist );
struct ap_List* adapted_approx_antipoles( struct ap_List *set, double radius );
struct ap_Point* approx_1_median( struct ap_List *set );
struct ap_List* check( struct ap_List *set, double radius, struct ap_Point *antipole );

#endif /* ANTIPOLE_H */

