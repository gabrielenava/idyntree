classdef FreeFloatingVel < SwigRef
  methods
    function this = swig_this(self)
      this = iDynTreeMEX(3, self);
    end
    function self = FreeFloatingVel(varargin)
      if nargin==1 && strcmp(class(varargin{1}),'SwigRef')
        if ~isnull(varargin{1})
          self.swigPtr = varargin{1}.swigPtr;
        end
      else
        tmp = iDynTreeMEX(1199, varargin{:});
        self.swigPtr = tmp.swigPtr;
        tmp.SwigClear();
      end
    end
    function varargout = resize(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1200, self, varargin{:});
    end
    function varargout = baseVel(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1201, self, varargin{:});
    end
    function varargout = jointVel(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1202, self, varargin{:});
    end
    function varargout = getNrOfDOFs(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1203, self, varargin{:});
    end
    function delete(self)
      if self.swigPtr
        iDynTreeMEX(1204, self);
        self.SwigClear();
      end
    end
  end
  methods(Static)
  end
end
