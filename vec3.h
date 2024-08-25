#ifndef VEC3_H

#define VEC3_H


using std::sqrt;

class vec3 {
	public:
		double n[3];
		
		vec3() : n{ 0,0,0 } {}
		vec3(double x, double y, double z) : n{ x,y,z } {}

		double x() const { return n[0]; }
		double y() const { return n[1]; }
		double z() const { return n[2]; }

		vec3 operator-() const { return vec3(-n[0], -n[1], -n[2]); }
		double operator[](int i) const { return n[i]; }
		double& operator[](int i) { return n[i]; }

		vec3& operator+=(const vec3& v) {
			n[0] += v.n[0];
			n[1] += v.n[1];
			n[2] += v.n[2];

			return *this;
		}

		vec3& operator*=(double t) {
			n[0] *= t;
			n[1] *= t;
			n[2] *= t;

			return *this;
		}

		vec3& operator/=(double t) {
			return *this *= 1 / t;
		}

		double length() const {
			return sqrt(length_squared());
		}

		double length_squared() const {
			return n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
		}

		bool near_zero() const {
			auto s = 1e-8;
			return (std::fabs(n[0]) < s) && (std::fabs(n[1]) < s) && (std::fabs(n[2]) < s);
		}

		static vec3 random() {
			return vec3(random_double(), random_double(), random_double());
		}

		static vec3 random(double min, double max) {
			return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
		}
};

using point = vec3;


//vec utility functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.n[0] << ' ' << v.n[1] << ' ' << v.n[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.n[0] + v.n[0], u.n[1] + v.n[1], u.n[2] + v.n[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.n[0] - v.n[0], u.n[1] - v.n[1], u.n[2] - v.n[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.n[0] * v.n[0], u.n[1] * v.n[1], u.n[2] * v.n[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.n[0], t * v.n[1], t * v.n[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.n[0] * v.n[0] + u.n[1] * v.n[1] + u.n[2] * v.n[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.n[1] * v.n[2] - u.n[2] * v.n[1],
		u.n[2] * v.n[0] - u.n[0] * v.n[2],
		u.n[0] * v.n[1] - u.n[1] * v.n[0]);
}

inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() < 1)
			return p;
	}
}

inline vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3& normal) {
	vec3 on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0)
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

#endif