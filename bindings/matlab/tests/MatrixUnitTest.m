function test_suite=MatrixUnitTest
    initTestSuite

function test_sparse_matrices
    iDynTreeLoad;
    rand('state',0);
    randSparse = sprand(10,20,0.5);
    randSparseId = iDynTree.MatrixDynSize();
    randSparseId.fromMatlab(randSparse);
    % Sparse matrix fromMatlab/toMatlab do not work correctly in octave
    if (not(exist ("OCTAVE_VERSION", "builtin") > 0))
        assertElementsAlmostEqual(randSparseId.toMatlab(),full(randSparse))
    end