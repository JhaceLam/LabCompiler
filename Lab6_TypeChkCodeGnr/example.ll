@a = global float 0xC0091EB860000000, align 4
@b = global [4 x [2 x [3 x i32]]] [[2 x [3 x i32]] [[3 x i32] [i32 0, i32 1, i32 2], [3 x i32] [i32 3, i32 4, i32 5]], [2 x [3 x i32]] zeroinitializer, [2 x [3 x i32]] zeroinitializer, [2 x [3 x i32]] zeroinitializer], align 16
@c = global [4 x float] [float 0x40091EB860000000, float 0x4010851EC0000000, float 0x4024000000000000, float 0x0], align 16
@idx1 = global i32 3, align 4
@idx2 = global i32 1, align 4
@idx3 = global i32 2, align 4

define void @fun([2 x [3 x i32]]* %t0) {
B6:
  %t7 = alloca [2 x [3 x i32]]*, align 8
  store [2 x [3 x i32]]* %t0, [2 x [3 x i32]]** %t7, align 4
  %t8 = load [2 x [3 x i32]]*, [2 x [3 x i32]]** %t7, align 8
  %t2 = load i32, i32* @idx1, align 4
  %t5 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %t8, i32 %t2
  %t3 = load i32, i32* @idx2, align 4
  %t9 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %t5, i32 0, i32 %t3
  %t4 = load i32, i32* @idx3, align 4
  %t10 = getelementptr inbounds [3 x i32], [3 x i32]* %t9, i32 0, i32 %t4
  store i32 20, i32* %t10, align 4
  ret void
}

define i32 @main() {
B11:
  %t12 = alloca float, align 8
  %t1 = sitofp i32 0 to float
  store float %t1, float* %t12, align 4
  %t3 = load float, float* %t12, align 4
  %t4 = fsub float 0x0, 0x40091EB860000000
  %t5 = fmul float %t3, %t4
  store float %t5, float* %t12, align 4
  ret i32 0
}

