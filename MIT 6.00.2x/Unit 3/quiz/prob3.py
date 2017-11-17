def song_playlist(songs, max_size):
    """
    songs: list of tuples, ('song_name', song_len, song_size)
    max_size: float, maximum size of total songs that you can fit

    Start with the song first in the 'songs' list, then pick the next 
    song to be the one with the lowest file size not already picked, repeat

    Returns: a list of a subset of songs fitting in 'max_size' in the order 
             in which they were chosen.
    """

    playlist = [] 

    remainingSize = max_size

    remainingSongs = songs
    
    if max_size >= remainingSongs[0][2]: 
    	playlist.append(remainingSongs[0][0]) 
    	remainingSize -= remainingSongs[0][2]
    	del remainingSongs[0]
    else: 
    	return playlist
    
    remainingSongs = sorted(remainingSongs, key=lambda song: song[2])

    for title, length, size in remainingSongs: 
    	if remainingSize < size: 
    		break 

    	playlist.append(title)
    	remainingSize -= size 

    return playlist