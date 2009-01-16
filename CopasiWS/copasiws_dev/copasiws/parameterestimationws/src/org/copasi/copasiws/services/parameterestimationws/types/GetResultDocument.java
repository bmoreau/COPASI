// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/CopasiWS/copasiws_dev/copasiws/parameterestimationws/src/org/copasi/copasiws/services/parameterestimationws/types/GetResultDocument.java,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: jdada $ 
//   $Date: 2008/11/11 12:19:51 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

/*
 * An XML document type.
 * Localname: GetResult
 * Namespace: http://parameterestimationws.services.copasiws.copasi.org/types
 * Java type: org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument
 *
 * Automatically generated - do not modify.
 */
package org.copasi.copasiws.services.parameterestimationws.types;


/**
 * A document containing one GetResult(@http://parameterestimationws.services.copasiws.copasi.org/types) element.
 *
 * This is a complex type.
 */
public interface GetResultDocument extends org.apache.xmlbeans.XmlObject {
    public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(GetResultDocument.class.getClassLoader(),
            "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                           .resolveHandle("getresult408cdoctype");

    /**
     * Gets the "GetResult" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult getGetResult();

    /**
     * Sets the "GetResult" element
     */
    void setGetResult(
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult getResult);

    /**
     * Appends and returns a new empty "GetResult" element
     */
    org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult addNewGetResult();

    /**
     * An XML GetResult(@http://parameterestimationws.services.copasiws.copasi.org/types).
     *
     * This is a complex type.
     */
    public interface GetResult extends org.apache.xmlbeans.XmlObject {
        public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(GetResult.class.getClassLoader(),
                "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                               .resolveHandle("getresultdf6belemtype");

        /**
         * Gets the "userId" element
         */
        java.lang.String getUserId();

        /**
         * Gets (as xml) the "userId" element
         */
        org.apache.xmlbeans.XmlString xgetUserId();

        /**
         * Sets the "userId" element
         */
        void setUserId(java.lang.String userId);

        /**
         * Sets (as xml) the "userId" element
         */
        void xsetUserId(org.apache.xmlbeans.XmlString userId);

        /**
         * Gets the "resourceId" element
         */
        int getResourceId();

        /**
         * Gets (as xml) the "resourceId" element
         */
        org.apache.xmlbeans.XmlInt xgetResourceId();

        /**
         * Sets the "resourceId" element
         */
        void setResourceId(int resourceId);

        /**
         * Sets (as xml) the "resourceId" element
         */
        void xsetResourceId(org.apache.xmlbeans.XmlInt resourceId);

        /**
         * Gets the "outputFormat" attribute
         */
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat.Enum getOutputFormat();

        /**
         * Gets (as xml) the "outputFormat" attribute
         */
        org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat xgetOutputFormat();

        /**
         * True if has "outputFormat" attribute
         */
        boolean isSetOutputFormat();

        /**
         * Sets the "outputFormat" attribute
         */
        void setOutputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat.Enum outputFormat);

        /**
         * Sets (as xml) the "outputFormat" attribute
         */
        void xsetOutputFormat(
            org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat outputFormat);

        /**
         * Unsets the "outputFormat" attribute
         */
        void unsetOutputFormat();

        /**
         * An XML outputFormat(@).
         *
         * This is an atomic type that is a restriction of org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument$GetResult$OutputFormat.
         */
        public interface OutputFormat extends org.apache.xmlbeans.XmlString {
            public static final org.apache.xmlbeans.SchemaType type = (org.apache.xmlbeans.SchemaType) org.apache.xmlbeans.XmlBeans.typeSystemForClassLoader(OutputFormat.class.getClassLoader(),
                    "schemaorg_apache_xmlbeans.system.parameterestimationwsTypeSystem")
                                                                                                                                   .resolveHandle("outputformat6de3attrtype");
            static final Enum TEXT = Enum.forString("text");
            static final Enum SBRML = Enum.forString("sbrml");
            static final int INT_TEXT = Enum.INT_TEXT;
            static final int INT_SBRML = Enum.INT_SBRML;

            org.apache.xmlbeans.StringEnumAbstractBase enumValue();

            void set(org.apache.xmlbeans.StringEnumAbstractBase e);

            /**
             * Enumeration value class for org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument$GetResult$OutputFormat.
             * These enum values can be used as follows:
             * <pre>
             * enum.toString(); // returns the string value of the enum
             * enum.intValue(); // returns an int value, useful for switches
             * // e.g., case Enum.INT_TEXT
             * Enum.forString(s); // returns the enum value for a string
             * Enum.forInt(i); // returns the enum value for an int
             * </pre>
             * Enumeration objects are immutable singleton objects that
             * can be compared using == object equality. They have no
             * public constructor. See the constants defined within this
             * class for all the valid values.
             */
            static final class Enum extends org.apache.xmlbeans.StringEnumAbstractBase {
                static final int INT_TEXT = 1;
                static final int INT_SBRML = 2;
                public static final org.apache.xmlbeans.StringEnumAbstractBase.Table table =
                    new org.apache.xmlbeans.StringEnumAbstractBase.Table(new Enum[] {
                            new Enum("text", INT_TEXT),
                            new Enum("sbrml", INT_SBRML),
                        });
                private static final long serialVersionUID = 1L;

                private Enum(java.lang.String s, int i) {
                    super(s, i);
                }

                /**
                 * Returns the enum value for a string, or null if none.
                 */
                public static Enum forString(java.lang.String s) {
                    return (Enum) table.forString(s);
                }

                /**
                 * Returns the enum value corresponding to an int, or null if none.
                 */
                public static Enum forInt(int i) {
                    return (Enum) table.forInt(i);
                }

                private java.lang.Object readResolve() {
                    return forInt(intValue());
                }
            }

            /**
             * A factory class with static methods for creating instances
             * of this type.
             */
            public static final class Factory {
                private Factory() {
                } // No instance of this class allowed

                public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat newValue(
                    java.lang.Object obj) {
                    return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat) type.newValue(obj);
                }

                public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat newInstance() {
                    return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                                           .newInstance(type,
                        null);
                }

                public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat newInstance(
                    org.apache.xmlbeans.XmlOptions options) {
                    return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult.OutputFormat) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                                           .newInstance(type,
                        options);
                }
            }
        }

        /**
         * A factory class with static methods for creating instances
         * of this type.
         */
        public static final class Factory {
            private Factory() {
            } // No instance of this class allowed

            public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult newInstance() {
                return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                          .newInstance(type,
                    null);
            }

            public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult newInstance(
                org.apache.xmlbeans.XmlOptions options) {
                return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument.GetResult) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                                          .newInstance(type,
                    options);
            }
        }
    }

    /**
     * A factory class with static methods for creating instances
     * of this type.
     */
    public static final class Factory {
        private Factory() {
        } // No instance of this class allowed

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument newInstance() {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .newInstance(type,
                null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument newInstance(
            org.apache.xmlbeans.XmlOptions options) {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .newInstance(type,
                options);
        }

        /** @param xmlAsString the string value to parse */
        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.lang.String xmlAsString)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(xmlAsString,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.lang.String xmlAsString, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(xmlAsString,
                type, options);
        }

        /** @param file the file from which to load an xml document */
        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.io.File file)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(file,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.io.File file, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(file,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.net.URL u)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(u,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.net.URL u, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(u,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.io.InputStream is)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(is,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.io.InputStream is, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(is,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.io.Reader r)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(r,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            java.io.Reader r, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException, java.io.IOException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(r,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            javax.xml.stream.XMLStreamReader sr)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(sr,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            javax.xml.stream.XMLStreamReader sr,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(sr,
                type, options);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            org.w3c.dom.Node node) throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(node,
                type, null);
        }

        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            org.w3c.dom.Node node, org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(node,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument parse(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return (org.copasi.copasiws.services.parameterestimationws.types.GetResultDocument) org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                                                                                                            .parse(xis,
                type, options);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.apache.xmlbeans.xml.stream.XMLInputStream newValidatingXMLInputStream(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                               .newValidatingXMLInputStream(xis,
                type, null);
        }

        /** @deprecated {@link XMLInputStream} */
        public static org.apache.xmlbeans.xml.stream.XMLInputStream newValidatingXMLInputStream(
            org.apache.xmlbeans.xml.stream.XMLInputStream xis,
            org.apache.xmlbeans.XmlOptions options)
            throws org.apache.xmlbeans.XmlException,
                org.apache.xmlbeans.xml.stream.XMLStreamException {
            return org.apache.xmlbeans.XmlBeans.getContextTypeLoader()
                                               .newValidatingXMLInputStream(xis,
                type, options);
        }
    }
}