/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/target/TargetImpl.h
 *
*/
#ifndef ZYPP_TARGET_TARGETIMPL_H
#define ZYPP_TARGET_TARGETIMPL_H

#include <iosfwd>

#include "zypp/base/ReferenceCounted.h"
#include "zypp/base/NonCopyable.h"
#include "zypp/base/PtrTypes.h"
#include "zypp/ResStore.h"

#include "zypp/Pathname.h"
#include "zypp/media/MediaAccess.h"
#include "zypp/Target.h"
#include "zypp/target/rpm/RpmDb.h"
#include "zypp/solver/detail/Types.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace target
  { /////////////////////////////////////////////////////////////////

    DEFINE_PTR_TYPE(TargetImpl);

    ///////////////////////////////////////////////////////////////////
    //
    //	CLASS NAME : TargetImpl
    //
    /** Base class for concrete Target implementations.
     *
     * Constructed by \ref TargetFactory. Public access via \ref Target
     * interface.
    */
    class TargetImpl : public base::ReferenceCounted, private base::NonCopyable
    {
      friend std::ostream & operator<<( std::ostream & str, const TargetImpl & obj );

    public:
      /** Ctor. */
      TargetImpl(const Pathname & root_r = "/");
      /** Dtor. */
      virtual ~TargetImpl();

      /** Null implementation */
      static TargetImpl_Ptr nullimpl();

    public:

      /** All resolvables in the target. */
      const ResStore & resolvables();

      /** Sort according to prereqs and media numbers */
      void getResolvablesToInsDel ( ResPool pool_r,
				    PoolItemList & dellist_r,
				    PoolItemList & instlist_r,
				    PoolItemList & srclist_r );

      /** Commit changes in the pool */
#warning Add support for multiple medias - eg. limit only to CD1
      void commit(ResPool pool_r);

      /** Commit ordered changes */
      void commit(const PoolItemList & items_r);

      /** Overload to realize stream output. */
      virtual std::ostream & dumpOn( std::ostream & str ) const
      { return str << "TargetImpl"; }

      /** The RPM database */
      rpm::RpmDb & rpm();

      /** If the package is installed and provides the file
	  Needed to evaluate split provides during Resolver::Upgrade() */
      bool providesFile (const std::string & name_str, const std::string & path_str) const;

    protected:
      /** All resolvables provided by the target. */
      ResStore _store;
      /** Path to the target */
      Pathname _root;
      /** RPM database */
      rpm::RpmDb _rpm;
    private:
      /** Null implementation */
      static TargetImpl_Ptr _nullimpl;
    };
    ///////////////////////////////////////////////////////////////////

    /** \relates TargetImpl Stream output */
    inline std::ostream & operator<<( std::ostream & str, const TargetImpl & obj )
    { return obj.dumpOn( str ); }

    /////////////////////////////////////////////////////////////////
  } // namespace target
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_TARGET_TARGETIMPL_H
