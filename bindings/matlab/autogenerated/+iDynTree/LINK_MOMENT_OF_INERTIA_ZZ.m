function v = LINK_MOMENT_OF_INERTIA_ZZ()
  persistent vInitialized;
  if isempty(vInitialized)
    vInitialized = iDynTreeMEX(0, 38);
  end
  v = vInitialized;
end
