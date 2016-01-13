classdef AngularMotionVector3Semantics < iDynTree.GeomVector3Semantics__AngularMotionVector3Semantics
  methods
    function self = AngularMotionVector3Semantics(varargin)
      self@iDynTree.GeomVector3Semantics__AngularMotionVector3Semantics(SwigRef.Null);
      if nargin==1 && strcmp(class(varargin{1}),'SwigRef')
        if varargin{1}~=SwigRef.Null
          self.swigPtr = varargin{1}.swigPtr;
        end
      else
        tmp = iDynTreeMEX(294, varargin{:});
        self.swigPtr = tmp.swigPtr;
        tmp.swigPtr = [];
      end
    end
    function delete(self)
      if self.swigPtr
        iDynTreeMEX(295, self);
        self.swigPtr=[];
      end
    end
  end
  methods(Static)
  end
end
