protobuf_decl.name = protobuf headers
protobuf_decl.input = PROTOS
protobuf_decl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.pb.h
protobuf_decl.commands = protoc --cpp_out=${QMAKE_FILE_IN_PATH} --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_decl.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_decl

protobuf_impl.name = protobuf sources
protobuf_impl.input = PROTOS
protobuf_impl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.pb.cc
protobuf_impl.depends = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.pb.h
protobuf_impl.commands = $$escape_expand(\n)
protobuf_impl.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_impl

grpc_decl.name = grpc headers
grpc_decl.input = PROTOS
grpc_decl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.grpc.pb.h
grpc_decl.commands = protoc --grpc_out=${QMAKE_FILE_IN_PATH} --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
grpc_decl.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += grpc_decl

grpc_impl.name = grpc sources
grpc_impl.input = PROTOS
grpc_impl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.grpc.pb.cc
grpc_impl.depends = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.grpc.pb.h
grpc_impl.commands = $$escape_expand(\n)
grpc_impl.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += grpc_impl


