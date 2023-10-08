FROM gcc as base

COPY . ./

RUN make clean && make

FROM ubuntu

WORKDIR /usr/src/app

ENV PORT=5672

COPY --from=base ./main ./

RUN chmod 777 ./main

EXPOSE $PORT

CMD ./main ${PORT}


