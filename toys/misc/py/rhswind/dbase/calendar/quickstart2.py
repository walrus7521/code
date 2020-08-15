#!/usr/bin/env python3

# https://developers.google.com/calendar/v3/reference/events/list
# https://karenapp.io/articles/how-to-automate-google-calendar-with-python-using-the-calendar-api/

from __future__ import print_function
import datetime
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request

# If modifying these scopes, delete the file token.pickle.
SCOPES = ['https://www.googleapis.com/auth/calendar.readonly']


service = None
creds = None

def list_all():
    global service
    global creds
    events = None
    page_token = None
    a_list = []
    while True:
        events = service.events().list(calendarId='primary', pageToken=page_token).execute()
        a_list.append(events)
        page_token = events.get('nextPageToken')
        if not page_token:
            break
    return a_list

def curr(date, numEvents):
    global service
    global creds
#   now = datetime.datetime.utcnow().isoformat() + 'Z' # 'Z' indicates UTC time
#   now = str(datetime.datetime.now().isoformat()) + 'Z' # 'Z' indicates UTC time
#   now = '2020-08-15T00:00:00.000000Z'
    now = date + 'T00:00:00.000000Z'
    print('Getting the upcoming {0} events since: {1}'.format(numEvents, date))
#   return
    events_result = service.events().list(calendarId='primary', timeMin=now,
                                        maxResults=int(numEvents), singleEvents=True,
                                        orderBy='startTime').execute()
    events = events_result.get('items', [])
    return events

def init():
    """Shows basic usage of the Google Calendar API.
    Prints the start and name of the next 10 events on the user's calendar.
    """
    global service
    global creds
    # The file token.pickle stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)
    service = build('calendar', 'v3', credentials=creds)

def cli():
    while True:
        cmd = input("> ") 
        if cmd == 'list':
            e_list = list_all()
            for el in e_list:
                for event in el['items']:
                    try:
                        start = event['start'].get('dateTime', event['start'].get('date'))
                        print(start, event['summary'])
                    except:
                        print("no summary")
        elif cmd == 'now':
            date = '2020-06-15'
            events = curr(date, 10)
            if not events:
                print('No upcoming events found.')
            for event in events:
                start = event['start'].get('dateTime', event['start'].get('date'))
                print(start, event['summary'])
        elif cmd == 'quit':
            return
        else:
            print("unknown command: ", cmd)

def main():
    init()
    cli()

if __name__ == '__main__':
    main()
