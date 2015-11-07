#############################################################################
# Makefile for building: Shapes
#############################################################################

####### Compiler flags

# Use this flag for a slower executable WITH debugging information
# COMPILEFLAGS  = -pipe -Wall -W -g
# Use this flag for a fast executable WITHOUT debugging information
 COMPILEFLAGS  = -pipe -Wall -W -DNDEBUG -O3

####### Files

SRCFILES      =	\
		RayApp \
		RayCanvas \
		MyRayCanvas \
		RenderThread \
		Shape \
		MySphere \
		MyCylinder \
		MyCube \
		MyCone \
		MyCamera \
		moc_RayApp \
		moc_RayCanvas \
		moc_RenderThread \
		main \

TARGET        = ray

###########################################################################
# DO NOT CHANGE BELOW THIS
###########################################################################

BASEDIR	      = /course/cs123

# Support code files specific for this assignment
TAOBJECTS     = \
		$(BASEDIR)/lib/gui/CS123OpenGLCanvas.o \
		$(BASEDIR)/lib/gui/moc_CS123OpenGLCanvas.o \
		$(BASEDIR)/lib/gui/CS123Canvas.o \
		$(BASEDIR)/lib/gui/moc_CS123Canvas.o \
		$(BASEDIR)/lib/gui/SceneviewCanvas.o \
		$(BASEDIR)/lib/gui/moc_SceneviewCanvas.o \
		$(BASEDIR)/lib/common/CS123MeshObjLoader.o \
		$(BASEDIR)/lib/common/CS123XmlSceneParser.o \
		$(BASEDIR)/lib/ta/TAShapes.o \
		$(BASEDIR)/lib/ta/TACamera.o \
		$(BASEDIR)/lib/ta/TASceneviewCanvas.o \
		$(BASEDIR)/lib/ta/TAIntersectCanvas.o \
		$(BASEDIR)/lib/ta/TARayCanvas.o \
		$(BASEDIR)/lib/ta/TATreeFlattener.o \
		$(BASEDIR)/lib/ta/AABB.o \
		$(BASEDIR)/lib/ta/Primitive.o \
		$(BASEDIR)/lib/ta/Ray.o \
		$(BASEDIR)/lib/ta/kdTree.o \
		$(BASEDIR)/lib/tinyxml/tinystr.o \
		$(BASEDIR)/lib/tinyxml/tinyxml.o \
		$(BASEDIR)/lib/tinyxml/tinyxmlerror.o \
		$(BASEDIR)/lib/tinyxml/tinyxmlparser.o \
		$(BASEDIR)/lib/common/CS123Image.o \

include $(BASEDIR)/include/Makefile.common

