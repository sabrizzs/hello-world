FROM gcc as base

COPY . ./

RUN make clean && make

FROM ubuntu

WORKDIR /usr/src/app

ENV PORT=5672

COPY --from=base ./broker ./

RUN chmod 777 ./broker

EXPOSE $PORT

CMD ./broker ${PORT}