#include "Material.h"

Material::Material(double k_a, double k_d, double k_s, double n_s, double k_reflex) :
    k_a(k_a),
    k_d(k_d),
    k_s(k_s),
    n_s(n_s),
    k_reflex(k_reflex) {
}

Material::Material(const Material& material) {
    k_a = material.k_a;
    k_d = material.k_d;
    k_s = material.k_s;
    n_s = material.n_s;
    k_reflex = material.k_reflex;
}

Material::~Material() {
}

std::ostream& operator<<(std::ostream& os, const Material& material) {
    return os << "Ambiant:\t" << material.k_a << std::endl
              << "Diffuse:\t" << material.k_d << std::endl
              << "Specular:\t" << material.k_s << std::endl
              << "Cos Power:\t" << material.n_s << std::endl
              << "Reflexion:\t" << material.k_reflex;
}
