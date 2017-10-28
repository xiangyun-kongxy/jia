//
// Created by xiangyun.kong on 8/5/16.
//
#include "version.hpp"

namespace pf {

    version::version(long master, long feature /*= -1L*/, long tag /*= -1L*/,
                     version *compatible /*= nullptr*/) {
        m_master     = master;
        m_feature    = feature;
        m_tag        = tag;
        m_compatible = compatible;
    }

    version::version(const version &v) {
        *this = v;
    }

    version::~version() {
        delete m_compatible;
    }

    bool version::compatible(const version &v) const {
        return _compatible_no_transfer(v) ||
                (m_compatible != nullptr &&
                m_compatible->compatible(v));
    }

    bool version::operator==(const version &v) const {
        return this->m_master  == v.m_master &&
               this->m_feature == v.m_feature &&
               this->m_tag     == v.m_tag;
    }

    const version& version::operator=(const version &v) {
        this->m_master = v.m_master;
        this->m_feature = v.m_feature;
        this->m_tag = v.m_tag;

        if (v.m_compatible != nullptr)
            this->m_compatible = new version(*v.m_compatible);
        else
            this->m_compatible = nullptr;

        return *this;
    }

    bool version::_compatible_no_transfer(const version& v) const {
        // only if each sub version compatible with each other
        return _compatible_single_version(this->m_master, v.m_master) &&
               _compatible_single_version(this->m_feature, v.m_feature) &&
               _compatible_single_version(this->m_tag, v.m_tag);
    }

    bool version::_compatible_single_version(long v1, long v2) const {
        // version -1L compatible which any other version
        return v1 == v2 || v1 == -1L || v2 == -1L;
    }

}
