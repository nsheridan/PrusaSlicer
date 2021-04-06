#ifndef slic3r_SLA_SuppotstIslands_LineUtils_hpp_
#define slic3r_SLA_SuppotstIslands_LineUtils_hpp_

#include <optional>
#include <tuple>
#include <string>
#include <map>
#include <libslic3r/Line.hpp>
#include <libslic3r/SVG.hpp>

namespace Slic3r::sla {

/// <summary>
/// Class which contain collection of static function
/// for work with Line and Lines.
/// QUESTION: Is it only for SLA?
/// </summary>
class LineUtils
{
public:
    LineUtils() = delete;

    /// <summary>
    /// Sort lines to be in counter clock wise order only by point Line::a and function std::atan2
    /// </summary>
    /// <param name="lines">Lines to be sort</param>
    /// <param name="center">Center for CCW order</param>
    static void sort_CCW(Lines &lines, const Point &center);

    /// <summary>
    /// Create line segment intersection of line and circle
    /// </summary>
    /// <param name="line">Input line.</param>
    /// <param name="center">Circle center.</param>
    /// <param name="radius">Circle radius.</param>
    /// <returns>Chord -> line segment inside circle</returns>
    static std::optional<Slic3r::Line> crop_line(const Line & line,
                                                 const Point &center,
                                                 double       radius);
    static std::optional<Slic3r::Linef> crop_line(const Linef & line,
                                                 const Point &center,
                                                 double       radius);
    /// <summary>
    /// Create line segment intersection of ray and circle, when exist
    /// </summary>
    /// <param name="ray">Input ray.</param>
    /// <param name="center">Circle center.</param>
    /// <param name="radius">Circle radius.</param>
    /// <returns>Chord -> line segment inside circle</returns>
    static std::optional<Slic3r::Line> crop_ray(const Line & ray,
                                                const Point &center,
                                                double       radius);
    static std::optional<Slic3r::Linef> crop_ray(const Linef & ray,
                                                const Point &center,
                                                double       radius);
    /// <summary>
    /// Create line segment intersection of half ray(start point and direction) and circle, when exist
    /// </summary>
    /// <param name="half_ray">Use Line::a as start point and Line::b as direction but no limit</param>
    /// <param name="center">Circle center.</param>
    /// <param name="radius">Circle radius.</param>
    /// <returns>Chord -> line segment inside circle</returns>
    static std::optional<Slic3r::Line> crop_half_ray(const Line & half_ray,
                                                     const Point &center,
                                                     double       radius);
    static std::optional<Slic3r::Linef> crop_half_ray(const Linef & half_ray,
                                                     const Point &center,
                                                     double       radius);

    /// <summary>
    /// check if line is parallel to Y
    /// </summary>
    /// <param name="line">Input line</param>
    /// <returns>True when parallel otherwise FALSE</returns>
    static bool is_parallel_y(const Line &line);
    static bool is_parallel_y(const Linef &line);

    /// <summary>
    /// Create parametric coeficient
    /// ax + by + c = 0
    /// Can't be parallel to Y axis - check by function is_parallel_y
    /// </summary>
    /// <param name="line">Input line - cant be parallel with y axis</param>
    /// <returns>a, b, c</returns>
    static std::tuple<double, double, double> get_param(const Line &line);
    static std::tuple<double, double, double> get_param(const Linef &line);

    /// <summary>
    /// Calculate distance between point and ray
    /// </summary>
    /// <param name="line">a and b are only for direction, not limit</param>
    /// <param name="p">Point in space</param>
    /// <returns>Euclid perpedicular distance</returns>
    static double perp_distance(const Linef &line, Vec2d p);

    /// <summary>
    /// Create cross product of line direction.
    /// When zero than they are parallel.
    /// </summary>
    /// <param name="first">First line</param>
    /// <param name="second">Second line</param>
    /// <returns>True when direction are same(scaled or oposit or combination) otherwise FALSE</returns>
    static bool is_parallel(const Line &first, const Line &second);

    /// <summary>
    /// Intersection of line - no matter on line limitation
    /// </summary>
    /// <param name="ray1">first line</param>
    /// <param name="ray2">second line</param>
    /// <returns>intersection point when exist</returns>
    static std::optional<Vec2d> intersection(const Line &ray1, const Line &ray2);

    /// <summary>
    /// Create direction from point a to point b
    /// Direction vector is represented as point
    /// </summary>
    /// <param name="line">input line</param>
    /// <returns>line direction</returns>
    static Point direction(const Line &line) { return line.b - line.a; }

    //                          line index, <a connection, b connection>
    using LineConnection = std::map<size_t, std::pair<size_t, size_t>>;
    /// <summary>
    /// Create data structure from exPolygon lines to find if two lines are connected
    /// !! not tested
    /// </summary>
    /// <param name="lines">Lines created from ExPolygon</param>
    /// <returns>map of connected lines.</returns>
    static LineConnection create_line_connection(const Lines &lines);

    /// <summary>
    /// Create data structure from exPolygon lines to store connected line indexes
    /// </summary>
    /// <param name="lines">Lines created from ExPolygon</param>
    /// <returns>map of connected lines over point line::b</returns>
    static std::map<size_t, size_t> create_line_connection_over_b(const Lines &lines);

    static void draw(SVG &       svg,
                     const Line &line,
                     const char *color        = "gray",
                     coordf_t    stroke_width = 0,
                     const char *name         = nullptr,
                     bool        side_points  = false,
                     const char *color_a      = "lightgreen",
                     const char *color_b      = "lightblue");
    static void draw(SVG &       svg,
                     const Lines &lines,
                     const char *color        = "gray",
                     coordf_t    stroke_width = 0,
                     bool ord         = false, // write order as text
                     bool        side_points  = false,
                     const char *color_a      = "lightgreen",
                     const char *color_b      = "lightblue");
};

} // namespace Slic3r::sla
#endif // slic3r_SLA_SuppotstIslands_LineUtils_hpp_