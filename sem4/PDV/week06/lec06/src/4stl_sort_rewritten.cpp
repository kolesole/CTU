// slightly cleaned up rewrite of the top-level sort function from Microsoft's STL
// (original definition at `execution:2745`)

template <typename It, typename Predicate>
void sort(It begin, It end, Predicate predicate) {
    try {
        // create a threadpool and a work queue
        auto _Work = _ThreadPool(_Threadpool_callback);
        // spawn worker threads
        _Work._Submit(_Threads - 1);

        // join the threadpool and get a reference to our local queue
        auto _My_ticket = _Work._Join_team();

        // value count
        auto _Ideal = end - begin;
        auto _Wi = _Sort_work_item(0, _Ideal, _Ideal);

        _Steal_result _Sr;
        do {
            // process work from local queue, starting with _Wi
            _Process_sort_queue(_UFirst, predicate, _My_ticket, _Wi);

            // try to steal work from other threads
            do {
                _Sr = _Work._Steal(_Wi);
            } while (_Sr == _Steal_result::_Abort);
            // we managed to steal some work, go back to the local queue

        } while (_Sr != _Steal_result::_Done);
        // ^ stop when there is no more work

    } catch (const _Parallelism_resources_exhausted&) {
        // could not parallelize, fall back to serial sort
        _Sort_unchecked(_UFirst, _ULast, _Ideal, predicate);
    }
}
