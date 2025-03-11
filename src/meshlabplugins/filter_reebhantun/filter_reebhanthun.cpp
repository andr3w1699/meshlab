/****************************************************************************
* MeshLab                                                           o o     *
* A versatile mesh processing toolbox                             o     o   *
*                                                                _   O  _   *
* Copyright(C) 2005                                                \/)\/    *
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

#include "filter_reebhanthun.h"

/**
 * @brief Constructor usually performs only two simple tasks of filling the two lists
 *  - typeList: with all the possible id of the filtering actions
 *  - actionList with the corresponding actions. If you want to add icons to
 *  your filtering actions you can do here by construction the QActions accordingly
 */

FilterReebHanTun::FilterReebHanTun()
{
	typeList = {FP_COMPUTE_REEB_HAN_THUN_};

	for(ActionIDType tt : types())
		actionList.push_back(new QAction(filterName(tt), this));
}


QString FilterReebHanTun::pluginName() const {
    return "ReebHanTun Filter";
}

/**
 * @brief ST() must return the very short string describing each filtering action
 * (this string is used also to define the menu entry)
 * @param filterId: the id of the filter
 * @return the name of the filter
 */
QString FilterReebHanTun::filterName(ActionIDType filter) const {
    return "ReebHanTun";
}

/**
 * @brief FilterSamplePlugin::pythonFilterName if you want that your filter should have a different
 * name on pymeshlab, use this function to return its python name.
 * @param f
 * @return
 */
QString FilterReebHanTun::pythonFilterName(ActionIDType f) const {
    return (f == FP_COMPUTE_REEB_HAN_THUN_) ? "compute_reeb_graph" : "unknown";
}


/**
 * @brief // Info() must return the longer string describing each filtering action
 * (this string is used in the About plugin dialog)
 * @param filterId: the id of the filter
 * @return an info string of the filter
 */
QString FilterReebHanTun::filterInfo(ActionIDType filter) const {
    return "Computes the Reeb Graph of the mesh using the ReebHanTun method.";
}


 /**
 * @brief The FilterClass describes in which generic class of filters it fits.
 * This choice affect the submenu in which each filter will be placed
 * More than a single class can be chosen.
 * @param a: the action of the filter
 * @return the class od the filter
 */
FilterPlugin::FilterClass FilterReebHanTun::getClass(const QAction*) const {
    return FilterPlugin::Smoothing;
}

/**
 * @brief FilterSamplePlugin::filterArity
 * @return
 */
FilterPlugin::FilterArity FilterReebHanTun::filterArity(const QAction* ) const {
    return SINGLE_MESH;
}

/**
 * @brief FilterSamplePlugin::getPreConditions
 * @return
 */
int FilterReebHanTun::getPreConditions(const QAction*) const
{
	return MeshModel::MM_NONE;
}

/**
 * @brief FilterSamplePlugin::postCondition
 * @return
 */
int FilterReebHanTun::postCondition(const QAction*) const
{
	return MeshModel::MM_VERTCOORD | MeshModel::MM_FACENORMAL | MeshModel::MM_VERTNORMAL;
}

/**
 * @brief This function define the needed parameters for each filter. Return true if the filter has some parameters
 * it is called every time, so you can set the default value of parameters according to the mesh
 * For each parameter you need to define,
 * - the name of the parameter,
 * - the default value
 * - the string shown in the dialog
 * - a possibly long string describing the meaning of that parameter (shown as a popup help in the dialog)
 * @param action
 * @param m
 * @param parlst
 */
RichParameterList FilterReebHanTun::initParameterList(const QAction *action,const MeshModel &m)
{
	RichParameterList parlst;
	switch(ID(action)) {
	case FP_COMPUTE_REEB_HAN_THUN_ :
		parlst.addParam(RichBool ("UpdateNormals", true, "Recompute normals", "Toggle the recomputation of the normals after the random displacement.\n\nIf disabled the face normals will remains unchanged resulting in a visually pleasant effect."));
		parlst.addParam(RichPercentage("Displacement", m.cm.bbox.Diag()/100.0f,0.0f,m.cm.bbox.Diag(), "Max displacement", "The vertex are displaced of a vector whose norm is bounded by this value"));
		parlst.addParam(RichInt("RandomSeed", 0, "Random Seed", "The seed used to generate random values. If seed is zero no random seed is used"));
		break;
	default :
		assert(0);
	}
	return parlst;
}

/**
 * @brief The Real Core Function doing the actual mesh processing.
 * @param action
 * @param md: an object containing all the meshes and rasters of MeshLab
 * @param par: the set of parameters of each filter
 * @param cb: callback object to tell MeshLab the percentage of execution of the filter
 * @return true if the filter has been applied correctly, false otherwise
 */
std::map<std::string, QVariant> FilterReebHanTun::applyFilter(const QAction * action, const RichParameterList & parameters, MeshDocument &md, unsigned int& /*postConditionMask*/, vcg::CallBackPos *cb)
{
	switch(ID(action)) {
	case FP_COMPUTE_REEB_HAN_THUN_ :
		break;
	default :
		wrongActionCalled(action);
	}
	return std::map<std::string, QVariant>();
}

MESHLAB_PLUGIN_NAME_EXPORTER(FilterReebHanTun)
