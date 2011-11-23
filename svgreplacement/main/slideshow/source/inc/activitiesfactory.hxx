/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef INCLUDED_SLIDESHOW_ACTIVITIESFACTORY_HXX
#define INCLUDED_SLIDESHOW_ACTIVITIESFACTORY_HXX

#include <com/sun/star/animations/XAnimate.hpp>
#include <com/sun/star/animations/XAnimateColor.hpp>

#include "animationactivity.hxx"
#include "activitiesqueue.hxx"
#include "event.hxx"
#include "eventqueue.hxx"
#include "shape.hxx"
#include "numberanimation.hxx"
#include "enumanimation.hxx"
#include "coloranimation.hxx"
#include "hslcoloranimation.hxx"
#include "stringanimation.hxx"
#include "boolanimation.hxx"
#include "pairanimation.hxx"

#include <boost/optional.hpp>
#include <boost/utility.hpp>

/* Definition of ActivitiesFactory class */

namespace slideshow {
namespace internal {

class ActivitiesFactory : private ::boost::noncopyable
{
public:
    /// Collection of common factory parameters
    struct CommonParameters
    {
        CommonParameters(
            const EventSharedPtr&                 rEndEvent,
            EventQueue&                           rEventQueue,
            ActivitiesQueue&                      rActivitiesQueue,
            double                                nMinDuration,
            sal_uInt32                            nMinNumberOfFrames,
            bool                                  bAutoReverse,
            ::boost::optional<double> const&      aRepeats,
            double                                nAcceleration,
            double                                nDeceleration,
            const ShapeSharedPtr&                 rShape,
            const ::basegfx::B2DVector&           rSlideBounds )
            : mpEndEvent( rEndEvent ),
              mrEventQueue( rEventQueue ),
              mrActivitiesQueue( rActivitiesQueue ),
              mnMinDuration( nMinDuration ),
              mnMinNumberOfFrames( nMinNumberOfFrames ),
              maRepeats( aRepeats ),
              mnAcceleration( nAcceleration ),
              mnDeceleration( nDeceleration ),
              mpShape( rShape ),
              maSlideBounds( rSlideBounds ),
              mbAutoReverse( bAutoReverse ) {}
        
        /// End event to fire when animation is over
        EventSharedPtr                                  mpEndEvent;
        
        /// Event queue to insert the end event into.
        EventQueue&                                     mrEventQueue;
        /// Event queue to insert the end event into.
        ActivitiesQueue&                                mrActivitiesQueue;
        
        /** Simple duration of the activity
            
            Specifies the minimal simple duration of the
            activity (minimal, because mnMinNumberOfFrames
            might prolongue the activity). According to SMIL,
            this might also be indefinite, which for our
            framework does not make much sense, though
            (wouldn't have a clue, then, how to scale the
            animation over time).
        */
        double                                          mnMinDuration;
        
        /** Minimal number of frames for this activity.
            
            This specifies the minimal number of frames this
            activity will display per simple duration. If less
            than this number are displayed until mnMinDuration
            is over, the activity will be prolongued until
            mnMinNumberOfFrames are rendered.
        */
        sal_uInt32                                      mnMinNumberOfFrames;
        
        /** Number of repeats for the simple duration
            
            This specified the number of repeats. The
            mnMinDuration times maRepeats yields the total
            duration of this activity. If this value is
            unspecified, the activity will repeat
            indefinitely.
        */
        ::boost::optional<double> const                 maRepeats;
        
        /// Fraction of simple time to accelerate animation
        double                                          mnAcceleration;
        
        /// Fraction of simple time to decelerate animation
        double                                          mnDeceleration;
        
        /// Shape, to get bounds from
        ShapeSharedPtr                                  mpShape;
        
        /// LayerManager, to get page size from
        ::basegfx::B2DVector                            maSlideBounds;
        
        /// When true, activity is played reversed after mnDuration.
        bool                                            mbAutoReverse;
    };
    
    /** Create an activity from an XAnimate node.
        
        This method creates an animated activity from the
        given XAnimate node, extracting all necessary
        animation parameters from that. Note that due to the
        animator parameter, the animation values must be
        convertible to a double value.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param xNode
        The SMIL animation node to animate
    */
    static AnimationActivitySharedPtr createAnimateActivity(
        const CommonParameters&                        rParms,
        const NumberAnimationSharedPtr&                rAnimator, 
        const ::com::sun::star::uno::Reference< 
        ::com::sun::star::animations::XAnimate >&   xNode );
    
    /** Create an activity from an XAnimate node.
        
        This method creates an animated activity from the
        given XAnimate node, extracting all necessary
        animation parameters from that. Note that due to the
        animator parameter, the animation values must be
        convertible to a double value.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param xNode
        The SMIL animation node to animate
    */
    static AnimationActivitySharedPtr createAnimateActivity(
        const CommonParameters&                        rParms,
        const EnumAnimationSharedPtr&                  rAnimator, 
        const ::com::sun::star::uno::Reference< 
        ::com::sun::star::animations::XAnimate >&      xNode );
    
    /** Create an activity from an XAnimate node.
        
        This method creates an animated activity from the
        given XAnimate node, extracting all necessary
        animation parameters from that. Note that due to the
        animator parameter, the animation values must be
        convertible to a color value.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param xNode
        The SMIL animation node to animate
    */
    static AnimationActivitySharedPtr createAnimateActivity(
        const CommonParameters&                        rParms,
        const ColorAnimationSharedPtr&                 rAnimator, 
        const ::com::sun::star::uno::Reference< 
        ::com::sun::star::animations::XAnimate >&      xNode );
    
    /** Create an activity from an XAnimate node.
        
        This method creates an animated activity from the
        given XAnimate node, extracting all necessary
        animation parameters from that. Note that due to the
        animator parameter, the animation values must be
        convertible to a color value.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param xNode
        The SMIL animation node to animate
    */
    static AnimationActivitySharedPtr createAnimateActivity(
        const CommonParameters&                            rParms,
        const HSLColorAnimationSharedPtr&                  rAnimator, 
        const ::com::sun::star::uno::Reference< 
        ::com::sun::star::animations::XAnimateColor >&     xNode );
    
    /** Create an activity from an XAnimate node.
        
        This method creates an animated activity from the
        given XAnimate node, extracting all necessary
        animation parameters from that. Note that due to the
        animator parameter, the animation values must be
        convertible to a pair of double values.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param xNode
        The SMIL animation node to animate
    */
    static AnimationActivitySharedPtr createAnimateActivity(
        const CommonParameters&                        rParms,
        const PairAnimationSharedPtr&                  rAnimator, 
        const ::com::sun::star::uno::Reference< 
        ::com::sun::star::animations::XAnimate >&   xNode );
    
    /** Create an activity from an XAnimate node.
        
        This method creates an animated activity from the
        given XAnimate node, extracting all necessary
        animation parameters from that. Note that due to the
        animator parameter, the animation values must be
        convertible to a string.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param xNode
        The SMIL animation node to animate
    */
    static AnimationActivitySharedPtr createAnimateActivity(
        const CommonParameters&                        rParms,
        const StringAnimationSharedPtr&                rAnimator, 
        const ::com::sun::star::uno::Reference< 
        ::com::sun::star::animations::XAnimate >&      xNode );
    
    /** Create an activity from an XAnimate node.
        
        This method creates an animated activity from the
        given XAnimate node, extracting all necessary
        animation parameters from that. Note that due to the
        animator parameter, the animation values must be
        convertible to a bool value.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param xNode
        The SMIL animation node to animate
    */
    static AnimationActivitySharedPtr createAnimateActivity(
        const CommonParameters&                        rParms,
        const BoolAnimationSharedPtr&                  rAnimator, 
        const ::com::sun::star::uno::Reference< 
        ::com::sun::star::animations::XAnimate >&      xNode );
    
    /** Create a simple activity for the given animator
        
        This method is suited to create activities for custom
        animations, which need a simple double value and lasts
        a given timespan. This activity always generates values
        from the [0,1] range.
        
        @param rParms
        Factory parameter structure
        
        @param rAnimator
        Animator sub-object
        
        @param bDirectionForward
        If true, the activity goes 'forward', i.e. from 0 to
        1. With false, the direction is reversed.
    */
    static AnimationActivitySharedPtr createSimpleActivity(
        const CommonParameters&         rParms,
        const NumberAnimationSharedPtr& rAnimator,
        bool                            bDirectionForward );
    
private:
    // default: constructor/destructor disabed
    ActivitiesFactory();
    ~ActivitiesFactory();
};

} // namespace internal
} // namespace presentation

#endif /* INCLUDED_SLIDESHOW_ACTIVITIESFACTORY_HXX */

