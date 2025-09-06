#pragma once

namespace test::helper {
/**
 * \brief In case of assertion failure, we rely on RAII to clean up, otherwise
 * ASan isn't very happy.
 *
 * \code{.cpp}
 * // add this where to_nuke is supposed to live.
 * Cleanup c{[&](){cleanup_fn(&to_nuke);}};
 * \endcode
 */
template <typename F> struct Cleanup {
    F m_cleanup;
    Cleanup(F &&t_cleanup) : m_cleanup{t_cleanup} {}
    ~Cleanup() { m_cleanup(); }
};
} // namespace test::helper
