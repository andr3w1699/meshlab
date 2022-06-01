/****************************************************************************
 * MeshLab                                                           o o     *
 * A versatile mesh processing toolbox                             o     o   *
 *                                                                _   O  _   *
 * Copyright(C) 2004-2022                                           \/)\/    *
 * Visual Computing Lab                                            /\/|      *
 * ISTI - Italian National Research Council                           |      *
 *                                                                    \      *
 * All rights reserved.                                                      *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
 * for more details.                                                         *
 *                                                                           *
 ****************************************************************************/

#ifndef MESHLAB_RICH_PARAMETER_H
#define MESHLAB_RICH_PARAMETER_H

#include <QDomElement>

#include <common/parameters/values.h>

class MeshDocument;

/**
 * @brief The RichParameter class
 *
 * The RichParameter class is a representation of a MeshLab parameter that contains
 * a value of a certain type (see the Value class and its specializations) plus
 * some other decorators, like a parameter description and a tooltip.
 *
 * All these decorators allow MeshLab to automatically design GUI interfaces for
 * every RichParameter spcialization.
 *
 * Every specialization must implement the following member functions:
 * - QString stringType() const : returns a string representation of the type of the RichParameter
 * - RichParameter* clone() const : returns a *new* object which is a clone of the RichParameter
 * - bool operator==(const RichParameter& rp): returns true if the two RichParameter are the same
 */
class RichParameter
{
public:
	RichParameter(const RichParameter& rp);
	RichParameter(RichParameter&& rp);
	RichParameter(
			const QString& nm,
			const Value& v,
			const QString& desc = QString(),
			const QString& tltip = QString(),
			bool isAdvanced = false,
			const QString& category = QString());
	virtual ~RichParameter();

	const QString& name() const;
	const Value& value() const;
	const QString& fieldDescription() const;
	const QString& toolTip() const;
	bool isAdvanced() const;
	const QString& category() const;

	template <class RichParam>
	bool isOfType() const
	{
		const RichParam* t = dynamic_cast<const RichParam*>(this);
		return (t != nullptr);
	}

	virtual QString stringType() const = 0;

	void setName(const QString& newName);
	void setValue(const Value& ov);

	virtual QDomElement fillToXMLDocument(QDomDocument& doc, bool saveDescriptionAndTooltip = true) const;

	//python names of paraeter
	QString pythonName() const;
	QString pythonType() const;

	virtual RichParameter* clone() const = 0;
	RichParameter& operator=(const RichParameter& rp);
	RichParameter& operator=(RichParameter&& rp);
	virtual bool operator==(const RichParameter& rp) = 0;

protected:
	QString pName;
	Value* val;
	QString fieldDesc;
	QString tooltip;
	bool advanced;
	QString pCategory;
};

class RichEnum : public RichParameter
{
public:
	RichEnum(
			const QString& nm,
			const int defval,
			const QStringList& values,
			const QString& desc = QString(),
			const QString& tltip = QString(),
			bool hidden = false,
			const QString& category = QString());
	~RichEnum();

	QString stringType() const;
	QDomElement fillToXMLDocument(QDomDocument& doc, bool saveDescriptionAndTooltip = true) const;

	RichEnum* clone() const;
	bool operator==(const RichParameter& rb);
	QStringList enumvalues;
};

class RichDynamicFloat : public RichParameter
{
public:
	RichDynamicFloat(
			const QString& nm,
			const Scalarm defval,
			const Scalarm minval,
			const Scalarm maxval,
			const QString& desc = QString(),
			const QString& tltip = QString(),
			bool hidden = false,
			const QString& category = QString());
	~RichDynamicFloat();

	QString stringType() const;
	QDomElement fillToXMLDocument(QDomDocument& doc, bool saveDescriptionAndTooltip = true) const;

	RichDynamicFloat* clone() const;
	bool operator==(const RichParameter& rb);
	Scalarm min;
	Scalarm max;
};

class RichOpenFile : public RichParameter
{
public:
	RichOpenFile(
			const QString& nm,
			const QString& directorydefval,
			const QStringList& exts,
			const QString& desc = QString(),
			const QString& tltip = QString(),
			bool hidden = false,
			const QString& category = QString());
	~RichOpenFile();

	QString stringType() const;
	QDomElement fillToXMLDocument(QDomDocument& doc, bool saveDescriptionAndTooltip = true) const;

	RichOpenFile* clone() const;
	bool operator==(const RichParameter& rb);
	QStringList exts;
};

class RichSaveFile : public RichParameter
{
public:
	RichSaveFile(
			const QString& nm,
			const QString& filedefval,
			const QString& ext,
			const QString& desc = QString(),
			const QString& tltip = QString(),
			bool hidden = false,
			const QString& category = QString());
	~RichSaveFile();

	QString stringType() const;
	QDomElement fillToXMLDocument(QDomDocument& doc, bool saveDescriptionAndTooltip = true) const;

	RichSaveFile* clone() const;
	bool operator==(const RichParameter& rb);
	QString ext;
};

class RichMesh : public RichParameter
{
public:
	RichMesh(
			const QString& nm,
			unsigned int meshindex,
			const MeshDocument* doc,
			const QString& desc = QString(),
			const QString& tltip = QString(),
			bool hidden = false,
			const QString& category = QString());
	~RichMesh();

	QString stringType() const;

	RichMesh* clone() const;
	bool operator==(const RichParameter& rb);
	const MeshDocument* meshdoc;
};

class RichParameterAdapter
{
public:
	static bool create(const QDomElement& np, RichParameter*& par);
};

#endif // MESHLAB_RICH_PARAMETER_H
