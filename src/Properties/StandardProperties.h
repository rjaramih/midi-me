#ifndef MIDIME_STANDARDPROPERTIES_H
#define MIDIME_STANDARDPROPERTIES_H

// Includes
#include "global.h"
#include "GenericProperty.h"
#include <map>

namespace MidiMe
{
	// Typedefs
	typedef std::map<string, Property *> PropertyMap;

	/** A property consisting of multiple other properties */
	class PROPERTIES_API CompoundProperty: public Property, public Property::Listener
	{
	protected:
		// Member variables
		PropertyMap m_properties;

	public:
		// Constructors and destructor
		CompoundProperty(PropertyCollection *pCollection, const string &name);
		virtual ~CompoundProperty();

		// Type
		static string type;
		const string &getType() const { return type; }

		// Property functions
		string toString() const;
		void fromString(const string &value);
		void fireChanged();

		// Properties
		//! @todo Rename to children in stead of properties
		const PropertyMap &getProperties() const { return m_properties; }
		bool addProperty(Property *pProperty);
		bool removeProperty(Property *pProperty);
		void clearProperties();

		unsigned int numProperties() const { return m_properties.size(); }
		Property *getProperty(const string &name) const;

	protected:
		// Property::Listener functions
		void onPropertyChanged(Property *pProperty);
	};

	/** A boolean */
	class PROPERTIES_API BoolProperty: public GenericProperty<bool>
	{
	public:
		BoolProperty(PropertyCollection *pCollection, const string &name, const GetFunctor &getter, const SetFunctor &setter)
			: GenericProperty<bool>(pCollection, name, getter, setter) {}

		static string type;
		const string &getType() const { return type; }

		string toString() const;
		void fromString(const string &value);
	};

	/** An integer number */
	class PROPERTIES_API IntProperty: public GenericProperty<int>
	{
	public:
		IntProperty(PropertyCollection *pCollection, const string &name, const GetFunctor &getter, const SetFunctor &setter)
			: GenericProperty<int>(pCollection, name, getter, setter) {}

		static string type;
		const string &getType() const { return type; }

		string toString() const;
		void fromString(const string &value);
	};

	/** A positive integer number */
	class PROPERTIES_API UIntProperty: public GenericProperty<unsigned int>
	{
	public:
		UIntProperty(PropertyCollection *pCollection, const string &name, const GetFunctor &getter, const SetFunctor &setter)
			: GenericProperty<unsigned int>(pCollection, name, getter, setter) {}

		static string type;
		const string &getType() const { return type; }

		string toString() const;
		void fromString(const string &value);
	};

	/** A floating point property */
	class PROPERTIES_API RealProperty: public GenericProperty<float>
	{
	public:
		RealProperty(PropertyCollection *pCollection, const string &name, const GetFunctor &getter, const SetFunctor &setter)
			: GenericProperty<float>(pCollection, name, getter, setter), m_min(0), m_max(1) {}

		static string type;
		const string &getType() const { return type; }

		string toString() const;
		void fromString(const string &value);

		float getMin() const { return m_min; }
		void setMin(float value) { m_min = value; }

		float getMax() const { return m_max; }
		void setMax(float value) { m_max = value; }

	protected:
		// Member variables
		float m_min, m_max;
	};

	/** A string property */
	class PROPERTIES_API StringProperty: public GenericProperty<const string &>
	{
	public:
		StringProperty(PropertyCollection *pCollection, const string &name, const GetFunctor &getter, const SetFunctor &setter)
			: GenericProperty<const string &>(pCollection, name, getter, setter) {}

		static string type;
		const string &getType() const { return type; }

		string toString() const;
		void fromString(const string &value);
	};
}

#endif // MIDIME_STANDARDPROPERTIES_H
