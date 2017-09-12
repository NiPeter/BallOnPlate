/*
 * IFilter.hpp
 *
 *  Created on: 17 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_TOUCHPANEL_IFILTER_HPP_
#define APPLICATION_USER_TOUCHPANEL_IFILTER_HPP_


template <typename OUT, typename IN>
class IFilter{
public:
	virtual ~IFilter(){};
	virtual OUT Filter( IN data ) = 0;
	virtual void Reset( void ) = 0;
};

#endif /* APPLICATION_USER_TOUCHPANEL_IFILTER_HPP_ */
