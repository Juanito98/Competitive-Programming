open Core

let triangular n = n * (n + 1) / 2

let triangular ~start ~_end =
  (* start + (start + 1) + (start + 2) + ... + end *)
  triangular _end - triangular (start - 1)

let part1 ~files ~available =
  let files = Deque.of_array files in
  let available = Queue.of_array available in
  let pos = ref 0 in
  let checksum = ref 0 in
  if Deque.length files > Queue.length available then Queue.enqueue available 0;
  while not (Deque.is_empty files) do
    (* One from files *)
    let id, cnt = Deque.dequeue_front files |> Option.value_exn in
    checksum := !checksum + (id * triangular ~start:!pos ~_end:(!pos + cnt - 1));
    pos := !pos + cnt;
    (* One from available *)
    let available = ref (Queue.dequeue available |> Option.value_exn) in
    while !available > 0 && not (Deque.is_empty files) do
      let id, cnt = Deque.dequeue_back files |> Option.value_exn in
      let used = min !available cnt in
      checksum :=
        !checksum + (id * triangular ~start:!pos ~_end:(!pos + used - 1));
      pos := !pos + used;
      if cnt > used then Deque.enqueue_back files (id, cnt - used);
      available := !available - used
    done
  done;
  !checksum

let part2 ~files ~available =
  let available = Array.map available ~f:(fun available -> ([], available)) in
  for j' = 1 to Array.length files do
    let j = Array.length files - j' in
    let id, cnt = Array.get files j in
    match
      Array.findi available ~f:(fun idx (_, available) ->
          available >= cnt && idx < j)
    with
    | None -> ()
    | Some (idx, (used, free)) ->
        Array.set available idx ((id, cnt) :: used, free - cnt);
        Array.set files j (-1, cnt)
  done;
  let arr =
    List.init
      (Array.length files + Array.length available)
      ~f:(fun idx ->
        let idx' = idx / 2 in
        if idx mod 2 = 0 then [ `File (Array.get files idx') ]
        else
          let files, available = Array.get available idx' in
          (List.rev files |> List.map ~f:(fun (id, cnt) -> `File (id, cnt)))
          @ [ `Available available ])
    |> List.concat
    |> List.filter_map ~f:(function
         | `File (id, cnt) when id < 0 -> Some (`Available cnt)
         | `File (_, cnt) when cnt = 0 -> None
         | `Available slot when slot = 0 -> None
         | x -> Some x)
  in
  List.fold arr ~init:(0, 0) ~f:(fun (pos, checksum) elem ->
      match elem with
      | `Available slot -> (pos + slot, checksum)
      | `File (id, cnt) ->
          ( pos + cnt,
            checksum + (id * triangular ~start:pos ~_end:(pos + cnt - 1)) ))
  |> snd

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let files, available =
    String.to_array input
    |> Array.mapi ~f:(fun idx c -> (idx, Char.to_string c |> Int.of_string))
    |> Array.partition_tf ~f:(fun (idx, _) -> idx mod 2 = 0)
    |> Tuple2.map ~f:(Array.map ~f:snd)
  in
  let files = Array.mapi files ~f:(fun idx elem -> (idx, elem)) in
  let checksum = solve part ~files ~available in
  print_s [%sexp (checksum : int)]

let%expect_test _ =
  let input = {|2333133121414131402|} in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 1928 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 2858 |}]
