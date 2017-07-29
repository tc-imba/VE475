import io

# sha3_step_chi
f = open('sha3_step_chi.h', 'w')
for k in range(0, 64):
    for i in range(0, 5):
        for j in range(0, 5):
            # sha3_temp[i][j] = A[i][j][k] ^ ((A[(i + 1) % 5][j][k] ^ (uint8_t) 1) & A[(i + 2) % 5][j][k]);
            f.write('sha3_temp[%d][%d] = A[%d][%d][%d] ^ ((A[%d][%d][%d] ^ (uint8_t) 1) & A[%d][%d][%d]);\n'
                  % (i, j, i, j, k, (i + 1) % 5, j, k, (i + 2) % 5, j, k))
    # for i in range(0, 5):
    #     for j in range(0, 5):
    #         # A[i][j][k] = sha3_temp[i][j];
    #         f.write('A[%d][%d][%d] = sha3_temp[%d][%d];\n' % (i, j, k, i, j))

f.close()
