#include "Side.h"

Side::Side(vector<Point> contour, int num)
{
 	_contour = contour;
	_id = num;

}


// standard distance calculation.
double Side::euclidean_distance(Point p1, Point p2) 
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;
 	return sqrt(dx * dx + dy * dy);
}

// Calculates the minimum distance between the set point and the curve
double Side::p_distance(Point p1, vector<Point> curve) {
    double d = 1E10; //Very large

    for (const auto& p : curve) {
        // Calculate the distance
        int x = p.x;
        int y = p.y;
        double e = euclidean_distance({ p1.x,p1.y }, { x,y });
        if (e < d) {
            d = e; // minimum distnce updated
        }
    }
    return d;
}

// Calculates the metrics of the similarity between the curves.
double Side::curve_metrix(vector<Point> curve1, vector<Point> curve2) {
    // for every point of curve1 it calculates the minimum distance
    // and then sums-up the distances, weighted by the number of points on curve1
    double d = 0;
    int counter = 0;
    for (const auto& p : curve1) {
        d += p_distance({ p.x,p.y }, curve2);
        counter++;
    }
    return d / counter;
}

// finds a curve centroid
Point Side::centroid(vector<Point> curve) {
    double mean_x = 0, mean_y = 0;
    int count = 0;

    for (const auto& p : curve) {
        mean_x += p.x;
        mean_y += p.y;
        count++;
    }
    mean_x = mean_x / count;
    mean_y = mean_y / count;

    return Point(mean_x, mean_y);
}

// Re-centeres the curve by centroid
vector<Point> Side::recenter(vector<Point> curve) {
    vector<Point> fixed_curve;
    Point center = centroid(curve);

    for (const auto& p : curve) {
        int x = p.x - center.x;
        int y = p.y - center.y;
        fixed_curve.push_back(Point(x, y));
    }
    return fixed_curve;
}

double Side::FindDifference(vector<Point> v1, vector<Point> v2)
{
    //flat side
    if (abs(euclidean_distance(v1[0], v1[v1.size() - 1]) - v1.size()) <= 15 || abs(euclidean_distance(v2[0], v2[v2.size() - 1]) - v2.size()) <= 15)
    {
        return -1;
    }


    vector<Point> curve1 = recenter(v1);
    vector<Point> curve2 = recenter(v2);

    // Calculate the euclidean distance between the curves. The less is the better similarity
    double dis = curve_metrix(curve1, curve2);

    cout << "euclian distance: " << dis << "\n";
    return dis;
}

