/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	devel/devel.dmacvicar/SQLiteBackend.h
*
*/
#ifndef DEVEL_DEVEL_DMACVICAR_SERIALIZE_H
#define DEVEL_DEVEL_DMACVICAR_SERIALIZE_H

#include <iosfwd>

#include "zypp/base/PtrTypes.h"
#include "Backend.h"

#include <zypp/Message.h>
#include <zypp/detail/MessageImpl.h>
#include <zypp/detail/PatchImpl.h>
#include <zypp/Patch.h>
#include <zypp/Package.h>
#include <zypp/Script.h>
#include <zypp/Message.h>
#include <zypp/Edition.h>
#include <zypp/CapSet.h>
#include <zypp/detail/PackageImpl.h>
#include <zypp/Script.h>
#include <zypp/detail/ScriptImpl.h>
#include <zypp/Resolvable.h>
#include <zypp/detail/ResolvableImpl.h>
#include <zypp/Capability.h>
#include <zypp/capability/CapabilityImpl.h>

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
namespace storage
{ /////////////////////////////////////////////////////////////////

template<class T>
std::string toXML( T obj ); //undefined

template<> // or constPtr?
std::string toXML( const Edition &edition );

template<> // or constPtr?
std::string toXML( const Arch &arch );

template<> // or constPtr?
std::string toXML( Capability &cap );

template<> // or constPtr?
std::string toXML( const CapSet &caps );

template<> // or constPtr?
std::string toXML( const Dependencies &dep );

/**
 * Serialize Resolvable properties
 * NOTE: This wont serialize child classes properties
 * Use castedToXML for that.
 */
template<> // or constPtr?
std::string toXML( Resolvable::constPtr obj );

/**
 * Serialize properties based in the specific kind of the Resolvable
 */
std::string castedToXML( Resolvable::constPtr ret );

/**
 * lack of instrospection sucks
 */
std::string resolvableTypeToString( Resolvable::constPtr resolvable, bool plural = false );

/**
 * lack of instrospection sucks
 */
std::string resolvableKindToString( Resolvable::Kind kind, bool plural = false );

template<> // or constPtr?
std::string toXML( Package::constPtr obj );

template<> // or constPtr?
std::string toXML( Script::constPtr obj );

template<> // or constPtr?
std::string toXML( Message::constPtr obj );

template<> // or constPtr?
std::string toXML( Patch::constPtr obj );

/////////////////////////////////////////////////////////////////
} // namespace devel.dmacvicar
	///////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
} // namespace devel
///////////////////////////////////////////////////////////////////
#endif // DEVEL_DEVEL_DMACVICAR_SQLITEBACKEND_H
