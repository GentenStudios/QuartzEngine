-- script to modify the way the perlin noise world generator works
-- use loadModel(script located in assets/scripts to load a model used by the world gen stuff)

models = {}  -- needed for tFileIO::readAllFilehe perlin noise stuff

function getSmoothingFactor(x, y, z)
    -- (x, y, z) is the chunk position
    return 32.0  -- default value
end