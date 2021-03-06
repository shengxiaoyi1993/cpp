/* soapStub.h
   Generated by gSOAP 2.8.51 for magic.h

gSOAP XML Web services tools
Copyright (C) 2000-2017, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/


#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"
#if GSOAP_VERSION != 20851
# error "GSOAP VERSION 20851 MISMATCH IN GENERATED CODE VERSUS LIBRARY CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes, Structs and Unions                                                *
 *                                                                            *
\******************************************************************************/

class vector;	/* magic.h:41 */
class matrix;	/* magic.h:54 */
struct ns1__magicResponse;	/* magic.h:68 */
struct ns1__magic;	/* magic.h:68 */

/* magic.h:41 */
#ifndef SOAP_TYPE_vector
#define SOAP_TYPE_vector (8)
/* SOAP encoded array of xsd:int schema type: */
class SOAP_CMAC vector {
      public:
        int *__ptr;
        int __size;
        /// Context that manages this object
        struct soap *soap;
        vector();
        vector(int _param_1);
        virtual ~vector();
        void resize(int _param_1);
        int &operator[](int _param_1) const;
      public:
        /// Return unique type id SOAP_TYPE_vector
        virtual int soap_type(void) const { return SOAP_TYPE_vector; }
        /// (Re)set members to default values
        virtual void soap_default(struct soap*);
        /// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
        virtual void soap_serialize(struct soap*) const;
        /// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
        virtual int soap_put(struct soap*, const char *tag, const char *type) const;
        /// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
        virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
        /// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
        virtual void *soap_get(struct soap*, const char *tag, const char *type);
        /// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
        virtual void *soap_in(struct soap*, const char *tag, const char *type);
        /// Return a new object of type vector, default initialized and not managed by a soap context
        virtual vector *soap_alloc(void) const { return SOAP_NEW(vector); }
        /// Friend allocator used by soap_new_vector(struct soap*, int)
        friend SOAP_FMAC1 vector * SOAP_FMAC2 soap_instantiate_vector(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* magic.h:54 */
#ifndef SOAP_TYPE_matrix
#define SOAP_TYPE_matrix (20)
/* SOAP encoded array of xsd:int[] schema type: */
class SOAP_CMAC matrix {
      public:
        vector *__ptr;
        int __size;
        /// Context that manages this object
        struct soap *soap;
        matrix();
        matrix(int _param_1, int _param_2);
        virtual ~matrix();
        void resize(int _param_1, int _param_2);
        vector &operator[](int _param_1) const;
      public:
        /// Return unique type id SOAP_TYPE_matrix
        virtual int soap_type(void) const { return SOAP_TYPE_matrix; }
        /// (Re)set members to default values
        virtual void soap_default(struct soap*);
        /// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
        virtual void soap_serialize(struct soap*) const;
        /// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
        virtual int soap_put(struct soap*, const char *tag, const char *type) const;
        /// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
        virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
        /// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
        virtual void *soap_get(struct soap*, const char *tag, const char *type);
        /// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
        virtual void *soap_in(struct soap*, const char *tag, const char *type);
        /// Return a new object of type matrix, default initialized and not managed by a soap context
        virtual matrix *soap_alloc(void) const { return SOAP_NEW(matrix); }
        /// Friend allocator used by soap_new_matrix(struct soap*, int)
        friend SOAP_FMAC1 matrix * SOAP_FMAC2 soap_instantiate_matrix(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* magic.h:68 */
#ifndef SOAP_TYPE_ns1__magicResponse
#define SOAP_TYPE_ns1__magicResponse (30)
/* complex XSD type 'ns1:magicResponse': */
struct SOAP_CMAC ns1__magicResponse {
      public:
        /** Optional element 'result' of XSD type 'ArrayOfArrayOfint' */
        matrix *result;
      public:
        /** Return unique type id SOAP_TYPE_ns1__magicResponse */
        int soap_type() const { return SOAP_TYPE_ns1__magicResponse; }
        /** Constructor with member initializations */
        ns1__magicResponse() : result() { }
        /** Friend allocator */
        friend SOAP_FMAC1 ns1__magicResponse * SOAP_FMAC2 soap_instantiate_ns1__magicResponse(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* magic.h:68 */
#ifndef SOAP_TYPE_ns1__magic
#define SOAP_TYPE_ns1__magic (31)
/* complex XSD type 'ns1:magic': */
struct SOAP_CMAC ns1__magic {
      public:
        /** Required element 'rank' of XSD type 'xsd:int' */
        int rank;
      public:
        /** Return unique type id SOAP_TYPE_ns1__magic */
        int soap_type() const { return SOAP_TYPE_ns1__magic; }
        /** Constructor with member initializations */
        ns1__magic() : rank() { }
        /** Friend allocator */
        friend SOAP_FMAC1 ns1__magic * SOAP_FMAC2 soap_instantiate_ns1__magic(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* magic.h:69 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (32)
/* SOAP_ENV__Header: */
struct SOAP_CMAC SOAP_ENV__Header {
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Header */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Header; }
        /** Constructor with member initializations */
        SOAP_ENV__Header() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Header * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* magic.h:69 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (33)
/* Type SOAP_ENV__Code is a recursive data type, (in)directly referencing itself through its (base or derived class) members */
/* SOAP_ENV__Code: */
struct SOAP_CMAC SOAP_ENV__Code {
      public:
        /** Optional element 'SOAP-ENV:Value' of XSD type 'xsd:QName' */
        char *SOAP_ENV__Value;
        /** Optional element 'SOAP-ENV:Subcode' of XSD type 'SOAP-ENV:Code' */
        struct SOAP_ENV__Code *SOAP_ENV__Subcode;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Code */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Code; }
        /** Constructor with member initializations */
        SOAP_ENV__Code() : SOAP_ENV__Value(), SOAP_ENV__Subcode() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Code * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* magic.h:69 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (35)
/* SOAP_ENV__Detail: */
struct SOAP_CMAC SOAP_ENV__Detail {
      public:
        char *__any;
        /** Any type of element 'fault' assigned to fault with its SOAP_TYPE_T assigned to __type */
        /** Do not create a cyclic data structure throught this member unless SOAP encoding or SOAP_XML_GRAPH are used for id-ref serialization */
        int __type;
        void *fault;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Detail */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Detail; }
        /** Constructor with member initializations */
        SOAP_ENV__Detail() : __any(), __type(), fault() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Detail * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* magic.h:69 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (37)
/* SOAP_ENV__Reason: */
struct SOAP_CMAC SOAP_ENV__Reason {
      public:
        /** Optional element 'SOAP-ENV:Text' of XSD type 'xsd:string' */
        char *SOAP_ENV__Text;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Reason */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Reason; }
        /** Constructor with member initializations */
        SOAP_ENV__Reason() : SOAP_ENV__Text() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Reason * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* magic.h:69 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (38)
/* SOAP_ENV__Fault: */
struct SOAP_CMAC SOAP_ENV__Fault {
      public:
        /** Optional element 'faultcode' of XSD type 'xsd:QName' */
        char *faultcode;
        /** Optional element 'faultstring' of XSD type 'xsd:string' */
        char *faultstring;
        /** Optional element 'faultactor' of XSD type 'xsd:string' */
        char *faultactor;
        /** Optional element 'detail' of XSD type 'SOAP-ENV:Detail' */
        struct SOAP_ENV__Detail *detail;
        /** Optional element 'SOAP-ENV:Code' of XSD type 'SOAP-ENV:Code' */
        struct SOAP_ENV__Code *SOAP_ENV__Code;
        /** Optional element 'SOAP-ENV:Reason' of XSD type 'SOAP-ENV:Reason' */
        struct SOAP_ENV__Reason *SOAP_ENV__Reason;
        /** Optional element 'SOAP-ENV:Node' of XSD type 'xsd:string' */
        char *SOAP_ENV__Node;
        /** Optional element 'SOAP-ENV:Role' of XSD type 'xsd:string' */
        char *SOAP_ENV__Role;
        /** Optional element 'SOAP-ENV:Detail' of XSD type 'SOAP-ENV:Detail' */
        struct SOAP_ENV__Detail *SOAP_ENV__Detail;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Fault */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Fault; }
        /** Constructor with member initializations */
        SOAP_ENV__Fault() : faultcode(), faultstring(), faultactor(), detail(), SOAP_ENV__Code(), SOAP_ENV__Reason(), SOAP_ENV__Node(), SOAP_ENV__Role(), SOAP_ENV__Detail() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Fault * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/


/* magic.h:38 */
#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (5)
typedef char *_XML;
#endif

/* magic.h:38 */
#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (6)
typedef char *_QName;
#endif

/* magic.h:38 */
#ifndef SOAP_TYPE_xsd__int
#define SOAP_TYPE_xsd__int (7)
typedef int xsd__int;
#endif

/******************************************************************************\
 *                                                                            *
 * Serializable Types                                                         *
 *                                                                            *
\******************************************************************************/


/* char has binding name 'byte' for type 'xsd:byte' */
#ifndef SOAP_TYPE_byte
#define SOAP_TYPE_byte (3)
#endif

/* xsd__int has binding name 'xsd__int' for type 'xsd:int' */
#ifndef SOAP_TYPE_xsd__int
#define SOAP_TYPE_xsd__int (7)
#endif

/* int has binding name 'int' for type 'xsd:int' */
#ifndef SOAP_TYPE_int
#define SOAP_TYPE_int (1)
#endif

/* matrix has binding name 'matrix' for type 'xsd:int[]' */
#ifndef SOAP_TYPE_matrix
#define SOAP_TYPE_matrix (20)
#endif

/* vector has binding name 'vector' for type 'xsd:int' */
#ifndef SOAP_TYPE_vector
#define SOAP_TYPE_vector (8)
#endif

/* struct SOAP_ENV__Fault has binding name 'SOAP_ENV__Fault' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (38)
#endif

/* struct SOAP_ENV__Reason has binding name 'SOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (37)
#endif

/* struct SOAP_ENV__Detail has binding name 'SOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (35)
#endif

/* struct SOAP_ENV__Code has binding name 'SOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (33)
#endif

/* struct SOAP_ENV__Header has binding name 'SOAP_ENV__Header' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (32)
#endif

/* struct ns1__magic has binding name 'ns1__magic' for type 'ns1:magic' */
#ifndef SOAP_TYPE_ns1__magic
#define SOAP_TYPE_ns1__magic (31)
#endif

/* struct ns1__magicResponse has binding name 'ns1__magicResponse' for type 'ns1:magicResponse' */
#ifndef SOAP_TYPE_ns1__magicResponse
#define SOAP_TYPE_ns1__magicResponse (30)
#endif

/* struct SOAP_ENV__Reason * has binding name 'PointerToSOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (40)
#endif

/* struct SOAP_ENV__Detail * has binding name 'PointerToSOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (39)
#endif

/* struct SOAP_ENV__Code * has binding name 'PointerToSOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (34)
#endif

/* matrix * has binding name 'PointerTomatrix' for type 'xsd:int[]' */
#ifndef SOAP_TYPE_PointerTomatrix
#define SOAP_TYPE_PointerTomatrix (28)
#endif

/* vector * has binding name 'PointerTovector' for type 'xsd:int' */
#ifndef SOAP_TYPE_PointerTovector
#define SOAP_TYPE_PointerTovector (21)
#endif

/* int * has binding name 'PointerToxsd__int' for type 'xsd:int' */
#ifndef SOAP_TYPE_PointerToxsd__int
#define SOAP_TYPE_PointerToxsd__int (9)
#endif

/* _QName has binding name '_QName' for type 'xsd:QName' */
#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (6)
#endif

/* _XML has binding name '_XML' for type '' */
#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (5)
#endif

/* char * has binding name 'string' for type 'xsd:string' */
#ifndef SOAP_TYPE_string
#define SOAP_TYPE_string (4)
#endif

/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stub Functions                                            *
 *                                                                            *
\******************************************************************************/

    SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns1__magic(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rank, matrix *result);

/******************************************************************************\
 *                                                                            *
 * Server-Side Operations                                                     *
 *                                                                            *
\******************************************************************************/

    /** Web service operation 'ns1__magic' (returns SOAP_OK or error code) */
    SOAP_FMAC5 int SOAP_FMAC6 ns1__magic(struct soap*, int rank, matrix *result);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns1__magic(struct soap*);

#endif

/* End of soapStub.h */
