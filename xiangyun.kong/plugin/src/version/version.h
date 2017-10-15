//
// Created by xiangyun.kong on 8/5/16.
//

#ifndef PLUGIN_VERSION_H
#define PLUGIN_VERSION_H


namespace pf {

    class version {
    public:
        /**
         * version -1L mean not specified. it compatible with any version
         */
        version(long master, long feature = -1L, long tag = -1L,
                version* compatible = nullptr);
        version(const version&);
        virtual ~version();

    public:
        /**
         * check if this is compatible with another. they are compatible if
         * 1. their sub-versions are equal or one of them is -1L
         * 2. their m_compatible, which is told compatible, is compatible with
         *    another
         *
         * compatible(≈) follows:
         *   - a≈b ≠ b≈a
         *   - a≈b and b≈c = a≈c
         *   - a≈a
         */
        virtual bool compatible(const version&) const;
        /**
         * @return true if their sub-versions are absolutely equal
         */
        virtual bool operator==(const version&) const;
        /**
         * deep copy full object
         */
        virtual const version& operator=(const version&);

    private:
        bool _compatible_no_transfer(const version&) const ;
        bool _compatible_single_version(long v1, long v2) const ;

    private:
        long m_master;
        long m_feature;
        long m_tag;

        version* m_compatible;
    };

}

#endif //PLUGIN_VERSION_H
