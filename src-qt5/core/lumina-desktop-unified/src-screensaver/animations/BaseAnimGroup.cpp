//===========================================
//  Lumina-DE source code
//  Copyright (c) 2015-2017, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
#include "BaseAnimGroup.h"

//Include all the known subclasses here, then add a unique ID for it to the functions at the bottom
//#include "SampleAnimation.h"
#include "Fireflies.h"
#include "Grav.h"
#include "SampleAnimation.h"
#include "Text.h"
#include "ImageSlideshow.h"
#include "VideoSlideshow.h"

//==============================
//     PLUGIN LOADING/LISTING
//==============================
BaseAnimGroup* BaseAnimGroup::NewAnimation(QString type, QWidget *parent, QSettings *set){
  //This is where we place all the known plugin ID's, and load the associated subclass
  if(type=="fireflies"){
    return (new FirefliesAnimation(parent,set));
  }else if(type == "grav") {
    return (new GravAnimation(parent, set));
  }else if(type == "text") {
    return (new TextAnimation(parent, set));
  }else if(type == "imageSlideshow") {
    return (new ImageAnimation(parent, set));
  }else if(type == "videoSlideshow") {
    return (new VideoAnimation(parent, set));
  }else {
    //Unknown screensaver, return a blank animation group
    return (new BaseAnimGroup(parent, set));
  }
}

QStringList BaseAnimGroup::KnownAnimations(){
  return (QStringList() << "imageSlideshow" /*<< "grav" << "text" << "imageSlideshow" << "fireflies"*/);
}
