//============================================================================

#pragma once
#include "FusionField.h"
#include "FusionPacket.h"
#include <assert.h>
#include <vector>

//============================================================================

namespace migme
{
    //============================================================================
    
    class IFusionPacketIO
    {
    public:
        virtual bool 			Exists(int fieldId) const = 0;
        
        virtual unsigned char	GetByte(int fieldId) const = 0;
        virtual void			SetByte(int fieldId, unsigned char value) = 0;
        
        virtual unsigned short 	GetUShort(int fieldId) const = 0;
        virtual void			SetUShort(int fieldId, unsigned short value) = 0;
        
        virtual unsigned int	GetUInt(int fieldId) const = 0;
        virtual void			SetUInt(int fieldId, unsigned int value) = 0;
        
        virtual long long		GetLong(int fieldId) const = 0;
        virtual void			SetLong(int fieldId, long long value) = 0;
        
        virtual unsigned long long	GetULong(int fieldId) const = 0;
        virtual void				SetULong(int fieldId, unsigned long long value) = 0;
        
        virtual std::string		GetString(int fieldId) const = 0;
        virtual void			SetString(int fieldId, const std::string& value) = 0;
        
        virtual std::vector<unsigned char> 	GetByteArray(int fieldId) const = 0;
        virtual void						SetByteArray(int fieldId, const std::vector<unsigned char>& value) = 0;
        
        virtual std::vector<std::string> 	GetStringArray(int fieldId, char separator) const = 0;
        virtual void						SetStringArray(int fieldId, const std::vector<std::string>& value, char separator) = 0;
    };
    
    //============================================================================
    
    template<int fieldId> class FusionPacketIO_ProxyBase
    {
    public:
        bool Exists() const						{ return packetIO.Exists(fieldId);  }
        
    protected:
        FusionPacketIO_ProxyBase(IFusionPacketIO& aPacketIO) : packetIO(aPacketIO)  { }
        
        IFusionPacketIO&	packetIO;
    };
    
    template<int fieldId> class FusionPacketIO_ByteProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_ByteProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        unsigned char GetWithDefault(unsigned char defaultValue) const { if(!this->Exists()) return defaultValue; else return (unsigned char) *this; }
        
        operator unsigned char() const 			{ return this->packetIO.GetByte(fieldId); }
        void operator=(unsigned char value) 	{ this->packetIO.SetByte(fieldId, value); }
    };
    
    template<int fieldId> class FusionPacketIO_UShortProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_UShortProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        unsigned short GetWithDefault(unsigned short defaultValue) const { if(!this->Exists()) return defaultValue; else return (unsigned short) *this; }
        
        operator unsigned short() const 		{ return this->packetIO.GetUShort(fieldId); }
        void operator=(unsigned short value) 	{ this->packetIO.SetUShort(fieldId, value); }
    };
    
    template<int fieldId> class FusionPacketIO_UIntProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_UIntProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        unsigned int GetWithDefault(unsigned int defaultValue) const { if(!this->Exists()) return defaultValue; else return (unsigned int) *this; }
        
        operator unsigned int() const 		{ return this->packetIO.GetUInt(fieldId); }
        void operator=(unsigned int value) 	{ this->packetIO.SetUInt(fieldId, value); }
    };
    
    template<int fieldId> class FusionPacketIO_LongProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_LongProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        long long GetWithDefault(long long defaultValue) const { if(!this->Exists()) return defaultValue; else return (long long) *this; }
        
        operator long long() const 			{ return this->packetIO.GetLong(fieldId); }
        void operator=(long long value) 	{ this->packetIO.SetLong(fieldId, value); }
    };
    
    template<int fieldId> class FusionPacketIO_ULongProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_ULongProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        unsigned long long GetWithDefault(unsigned long long defaultValue) const 	{ if(!this->Exists()) return defaultValue; else return (unsigned long long) *this; }
        unsigned long long GetWithDefault(unsigned long long (*fn)()) const 		{ if(!this->Exists()) return (*fn)(); else return (unsigned long long) *this; }
        
        operator unsigned long long() const 		{ return this->packetIO.GetULong(fieldId); }
        void operator=(unsigned long long value) 	{ this->packetIO.SetULong(fieldId, value); }
    };
    
    template<int fieldId> class FusionPacketIO_StringProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_StringProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        std::string GetWithDefault(const std::string& defaultValue=EMPTY_STRING) const { if(!this->Exists()) return defaultValue; else return (std::string) *this; }
        
        operator std::string() const 				{ return this->packetIO.GetString(fieldId); }
        void operator=(const std::string& value) 	{ this->packetIO.SetString(fieldId, value); }
        
        bool operator==(const std::string& a) const	{ return (std::string) *this == a; }
    };
    
    template<int fieldId> class FusionPacketIO_ByteArrayProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_ByteArrayProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        operator std::vector<unsigned char>() const 				{ return this->packetIO.GetByteArray(fieldId); }
        void operator=(const std::vector<unsigned char>& value) 	{ this->packetIO.SetByteArray(fieldId, value); }
        
        bool operator==(const std::vector<unsigned char>& a) const	{ return (std::vector<unsigned char>) *this == a; }
    };
    
    template<int fieldId, char separator> class FusionPacketIO_StringArrayProxy : public FusionPacketIO_ProxyBase<fieldId>
    {
    public:
        FusionPacketIO_StringArrayProxy(IFusionPacketIO& packetIO) : FusionPacketIO_ProxyBase<fieldId>(packetIO) { }
        
        std::vector<std::string> GetWithDefault() const			{ if(!this->Exists()) return {}; else return (std::vector<std::string>) *this; }
        
        operator std::vector<std::string>() const 				{ return this->packetIO.GetStringArray(fieldId, separator); }
        void operator=(const std::vector<std::string>& value) 	{ this->packetIO.SetStringArray(fieldId, value, separator); }
        
        bool operator==(const std::vector<std::string>& a) const	{ return (std::vector<std::string>) *this == a; }
    };
    
    //============================================================================
    
    template<typename T, int F> struct StorageTypeToFusionPacketIOType;
    template<int F> struct StorageTypeToFusionPacketIOType<Byte, F> 		{ typedef FusionPacketIO_ByteProxy<F> PacketIOType; };
    template<int F> struct StorageTypeToFusionPacketIOType<UShort, F> 		{ typedef FusionPacketIO_UShortProxy<F> PacketIOType; };
    
    template<int fieldId, typename E, typename S> class FusionPacketIO_EnumProxy
    {
    private:
        typedef typename StorageTypeToFusionPacketIOType<S, fieldId>::PacketIOType Implementation;
        Implementation impl;
        
    public:
        FusionPacketIO_EnumProxy(IFusionPacketIO& packetIO) : impl(packetIO) { }
        
        E GetWithDefault(E defaultValue) const { if(!impl.Exists()) return defaultValue; else return (E) *this; }
        
        operator E() const 			{ return (E) (typename S::NativeType) impl; }
        void operator=(E value) 	{ impl = (typename S::NativeType) value; 	}
        
        bool operator==(E a) const	{ return (E) *this == a; 					}
    };
    
    //============================================================================
    
    class MimeDataIOBase : public IFusionPacketIO
    {
    public:
        MimeDataIOBase(const std::vector<unsigned char>& aData) : data(aData) { }
        
    protected:
        bool HasFieldId(int fieldId) const;
        const FusionField* GetFieldById(int fieldId) const;
        
    private:
        const std::vector<unsigned char>& data;
    };
    
    class MimeDataIO : public MimeDataIOBase
    {
    public:
        MimeDataIO(const std::vector<unsigned char>& data) : MimeDataIOBase(data) { }
        
        virtual bool 			Exists(int fieldId) const 							{ return HasFieldId(fieldId);				}
        
        virtual unsigned char	GetByte(int fieldId) const 							{ return GetFieldById(fieldId)->AsByte(); 	}
        virtual void			SetByte(int fieldId, unsigned char value)			{ assert(false); }
        
        virtual unsigned short 	GetUShort(int fieldId) const						{ return GetFieldById(fieldId)->AsUShort(); }
        virtual void			SetUShort(int fieldId, unsigned short value) 		{ assert(false); }
        
        virtual unsigned int	GetUInt(int fieldId) const							{ return GetFieldById(fieldId)->AsUInt(); 	}
        virtual void			SetUInt(int fieldId, unsigned int value) 			{ assert(false); }
        
        virtual long long		GetLong(int fieldId) const							{ return GetFieldById(fieldId)->AsLong(); 	}
        virtual void			SetLong(int fieldId, long long value) 				{ assert(false); }
        
        virtual unsigned long long	GetULong(int fieldId) const						{ return GetFieldById(fieldId)->AsULong(); 	}
        virtual void				SetULong(int fieldId, unsigned long long value) { assert(false); }
        
        virtual std::string		GetString(int fieldId) const 						{ return GetFieldById(fieldId)->AsString(); }
        virtual void			SetString(int fieldId, const std::string& value)	{ assert(false); }
        
        virtual std::vector<unsigned char> 	GetByteArray(int fieldId) const 		{ return GetFieldById(fieldId)->AsByteArray(); }
        virtual void						SetByteArray(int fieldId, const std::vector<unsigned char>& value) { assert(false); }
        
        virtual std::vector<std::string> 	GetStringArray(int fieldId, char separator) const		{ return GetFieldById(fieldId)->AsStringArray(separator); }
        virtual void						SetStringArray(int fieldId, const std::vector<std::string>& value, char separator) { assert(false); }
    };
    
    //============================================================================
    
    class FusionPacketIO : public IFusionPacketIO
    {
    public:
        FusionPacketIO(const FusionPacket& aPacket) : packet(aPacket) { }
        
        virtual bool 			Exists(int fieldId) const 							{ return packet.HasFieldId(fieldId);				}
        
        virtual unsigned char	GetByte(int fieldId) const 							{ return packet.GetFieldById(fieldId)->AsByte(); 	}
        virtual void			SetByte(int fieldId, unsigned char value)			{ assert(false); }
        
        virtual unsigned short 	GetUShort(int fieldId) const						{ return packet.GetFieldById(fieldId)->AsUShort(); 	}
        virtual void			SetUShort(int fieldId, unsigned short value) 		{ assert(false); }
        
        virtual unsigned int	GetUInt(int fieldId) const							{ return packet.GetFieldById(fieldId)->AsUInt(); 	}
        virtual void			SetUInt(int fieldId, unsigned int value) 			{ assert(false); }
        
        virtual long long		GetLong(int fieldId) const							{ return packet.GetFieldById(fieldId)->AsLong(); 	}
        virtual void			SetLong(int fieldId, long long value) 				{ assert(false); }
        
        virtual unsigned long long	GetULong(int fieldId) const						{ return packet.GetFieldById(fieldId)->AsULong(); 	}
        virtual void				SetULong(int fieldId, unsigned long long value) { assert(false); }
        
        virtual std::string		GetString(int fieldId) const 						{ return packet.GetFieldById(fieldId)->AsString(); 	}
        virtual void			SetString(int fieldId, const std::string& value)	{ assert(false); }
        
        virtual std::vector<unsigned char> 	GetByteArray(int fieldId) const 		{ return packet.GetFieldById(fieldId)->AsByteArray(); }
        virtual void						SetByteArray(int fieldId, const std::vector<unsigned char>& value) { assert(false); }
        
        virtual std::vector<std::string> 	GetStringArray(int fieldId, char separator) const		{ return packet.GetFieldById(fieldId)->AsStringArray(separator); }
        virtual void						SetStringArray(int fieldId, const std::vector<std::string>& value, char separator) { assert(false); }
        
    private:
        const FusionPacket& packet;
    };
    
    //============================================================================
} // namespace migme
//============================================================================
